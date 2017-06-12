#include <cstdio>
#include <chrono>
#include <math.h>
#include <vector>
#include <queue>
#include <stack>
#include "../include/matgraph.h"
#include <boost/graph/push_relabel_max_flow.hpp>
#include "../../common/mem_used.hpp"

using namespace std;
using namespace boost;

// graph element descriptors
typedef adjacency_list_traits<vecS,vecS,directedS>::vertex_descriptor FlowNode;
typedef adjacency_list_traits<vecS,vecS,directedS>::edge_descriptor FlowEdge;
 
// a directed graph with reverse edges
struct VertexInformation {};
typedef unsigned Capacity;
struct EdgeInformation {
  Capacity edge_capacity;
  Capacity edge_residual_capacity;
  FlowEdge reverse_edge;
};
 
typedef adjacency_list<vecS,vecS,directedS,VertexInformation,EdgeInformation> FlowGraph;
 
static unsigned int NUM_EXP = 10;

void read_parameters(int argc, char **argv, unsigned int *op);
void usage(char **argv);

// Read a graph in DIMACS format from an input stream and return a Graph
void read_dimacs_flow_matching_graph(FlowGraph& g, std::istream& in, unsigned int* n, unsigned int* m, unsigned int *s, unsigned int *t) {

	std::string line="", dummy;
	while (line[0] != 'p' || line[1] != ' ' || line[2] != 'e' || line[3] != 'd' || line[4] != 'g' || line[5] != 'e'){
        getline(in,line);
    }
 
  	//get nodes and edges
    sscanf(line.c_str(), "p edge %u %u\n", n, m);
	for(unsigned int x=0;x<*n+2;x++)
		add_vertex(g);
  	
  	*s = 0;
  	*t = *n+1;
  	  	
  	unsigned i=0;
  	while (i<*m) {
    	getline(in,line);
    	if (line[0] == 'e' && line[1] == ' ') {
      		unsigned int u,v;
      		sscanf(line.c_str(), "e %u %u\n", &u, &v);
        	
        	if(u > *n/2){
        	    unsigned int temp = u;
        	    u = v;
        	    v = temp;
        	}
        		
      		FlowEdge e1, e2;
            bool in1, in2;
            tie(e1, in1) = add_edge(u, v, g);
            tie(e2, in2) = add_edge(v, u, g);
            
            g[e1].edge_capacity = 1;
            g[e2].edge_capacity = 0;
            g[e1].reverse_edge = e2;
            g[e2].reverse_edge = e1;
      		
      		i++;
    	}
  	}
  	
  	for(unsigned int i=1;i<=*n/2;i++){
  	    //connect source to all in v1
  	    FlowEdge e1, e2; 
        bool in1, in2;   
  	    tie(e1, in1) = add_edge(*s, i, g);
        tie(e2, in2) = add_edge(i, *s, g);    
        g[e1].edge_capacity = 1;
        g[e2].edge_capacity = 0;
        g[e1].reverse_edge = e2;
        g[e2].reverse_edge = e1;
        
        //connect all v2 to target
        FlowEdge e3, e4;    
  	    tie(e3, in1) = add_edge(i+(*n/2), *t, g);
        tie(e4, in2) = add_edge(*t, i+(*n/2), g);    
        g[e3].edge_capacity = 1;
        g[e4].edge_capacity = 0;
        g[e3].reverse_edge = e4;
        g[e4].reverse_edge = e3;
  	}

} 

//null node: when the vertex is not matched to any other valid vertex
static const unsigned int NULL_NODE = std::numeric_limits<unsigned int>::max();

struct HTreeNode{
    bool edge_used;
    unsigned int dest; //desteny of edge in H tree backward search
    
    HTreeNode(){
        edge_used = false;
    }
};

struct Matching{
    unsigned int card; //set cardinality
    vector<unsigned int> m; //vector of mates
    
    Matching(unsigned int sz, unsigned int def=NULL_NODE){
        card = 0;
        m.assign(sz, def);
    }
};

struct TestData{
    unsigned int phases; //number of phases (max is sqrt(n))
    unsigned int dfsiter; //iterations of the DFS extract_paths (max is m+n)
    unsigned int matching;
    long double time;
    size_t mem;
};


//BFS
bool search_paths_test(const Graph& g, const vector<unsigned int>& v1, vector<HTreeNode>& h, const vector<Edge>& pe, Matching& mat){    
    vector<bool> visited(num_vertices(g), false);
    //vector<unsigned int> dist(num_vertices(g), 0);
    std::queue<unsigned int> u1, u2;
    
    //get free nodes in v1 into queue u1
    for(unsigned int i=0;i<v1.size();i++){
        if(mat.m[v1[i]] == NULL_NODE)
            u1.push(v1[i]);
    }
    
    
    bool found = false;
    do{
        //if there is no vertex in u1, can't continue
        if(u1.size() == 0)
            break;
            
        //BFS: select neighbors in V2 throughout free edges    
        while(u1.size() > 0){
            unsigned int u = u1.front();
            visited[u] = true;
            u1.pop();
            
            graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		    for(tie(ie, fe) = out_edges(u, g); ie != fe; ie++){
			    unsigned int v = target(*ie, g);
			    if(not visited[v]){
			        //dist[v] = dist[u]+1;
			        u2.push(v);
			        h[g[*ie].id].edge_used = true; //mark edge as used in H
			        h[g[*ie].id].dest = u;
			    }
			}
        }
        
        //if there is no vertex in u2 can't continue
        if(u2.size() == 0)
            break;
            
        //BFS: select neighbors in V1 throughout matched edges
        while(u2.size() > 0){
            unsigned int u = u2.front();
            visited[u] = true;
            u2.pop();
            
            if(mat.m[u] == NULL_NODE){ //free way found
                found = true;
            }else{
                unsigned int v = mat.m[u];
                if(not visited[v]){
                    //dist[v] = dist[u]+1;
                    u1.push(v);
                    Edge e = pe[u];
                    h[g[e].id].edge_used = true;
                    h[g[e].id].dest = u;
                }
            }
        }   
    }while(not found); 
    
    //return wheter a path was found or not
    return found;
}

bool extract_paths_test(const Graph& g, const vector<unsigned int>& v2, vector<HTreeNode>& h, vector<Edge>& pe, Matching& mat, TestData& td){
    vector<bool> visited(num_vertices(g), false);
    unsigned int mp = mat.card;
    
    //for each free vertex in v2 run a DFS : TODO: check complexity, should be O(m+n)
    for(unsigned int i=0;i<v2.size();i++){
        if(mat.m[v2[i]] != NULL_NODE) continue;
        
        std::stack<unsigned int> s;
        std::stack<Edge> path;
        s.push(v2[i]);
        
        bool found_path = false;
        //DFS search for paths in the H tree
        while(s.size() > 0 && not found_path){
            unsigned int u = s.top();
            s.pop();
            if(visited[u]) continue;            
            visited[u] = true;

            graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		    for(tie(ie, fe) = out_edges(u, g); ie != fe; ie++){
		        td.dfsiter += 1;
    		    unsigned int v = target(*ie, g);
    		    //edge should be used in tree H and its destination in the reversed DAG cannot be u itself (it would mean another edge of same class)
		        if(not h[g[*ie].id].edge_used || h[g[*ie].id].dest == u) continue;
                
                if(not visited[v]){
                    s.push(v);
                    path.push(*ie);
                    if(mat.m[v] == NULL_NODE){ //if v is free, then it is in V1 and we found what we wanted
                       found_path = true;   //set that a path has been found
                       visited[v] = true;   //mark node v as visited so that it is not used in another path
                       break; //a valid path has been found, stop search
                    }
                }  
			}
        }
        
        //In case a M-alternating path has been found
        if(found_path){         
            bool free_edge = true; //indicates wheter the current edge being processed is free or not (M-alternating path)
            unsigned int next = target(path.top(), g); //indicates the next node in the path from v1 -> v2
            
            while(next != v2[i]){ //while the free vertex in v2 has not been reached
                //get an edge from the path stack
                Edge e = path.top();
                path.pop();
                
                //check if the edge belongs to this path (it may not)
                if(next != target(e, g)) continue;
                next = source(e,g);
                
                //Check if it is a matched edge, in this case there is nothing to do
                if(not free_edge){
                    free_edge = true;
                    continue;
                }
                
                //update the matching information (free edge becomes matched: update matching of both vertices)
                mat.m[source(e,g)] = target(e,g);
                mat.m[target(e,g)] = source(e,g);
                
                pe[source(e,g)] = e;
                pe[target(e,g)] = e;
                //set the next edge as matched (M-alternating path)
                free_edge = false;
            }
            
            //always increases by 1 if a path is found
            mat.card += 1;
        }
    }
    
    //a path was found
    if(mp < mat.card)
        return true;
    
    return false;
}

TestData hopcroft_karp_test(const Graph& g){
    TestData td;
    
    unsigned int n = num_vertices(g);
    unsigned int m = num_edges(g);
    vector<Edge> pe(n, Edge());
    vector<HTreeNode> h(num_edges(g)); //hungarian tree H
    Matching mat(num_vertices(g), NULL_NODE); //matching set M
    
    td.mem = memory_used();
    
    std::chrono::time_point<std::chrono::system_clock> tstart, tend;
    std::chrono::duration<long double> elapsed_seconds;
    tstart = std::chrono::system_clock::now();  
    
    //default definition of vertex sets v1 and v2: v1 U v2 = V : G=(V,E)    
    vector<unsigned int> v1(n/2);
    vector<unsigned int> v2(n/2);
    for(unsigned int i=0;i<n/2;i++){
        v1[i] = i;
        v2[i] = i+n/2;    
    }   
    
    //the main loop of the algorithm 
    td.dfsiter = 0;
    td.phases = 0;   
    while(search_paths_test(g, v1, h, pe, mat)){
        unsigned int mdi = td.dfsiter;
        td.dfsiter = 0;
        bool has_extract = extract_paths_test(g, v2, h, pe, mat, td);
        td.dfsiter = max(td.dfsiter, mdi);
        if(not has_extract)
            break;           
        h.assign(m, HTreeNode());
                        
        td.phases += 1;
    }
    
    tend = std::chrono::system_clock::now();
	elapsed_seconds = tend-tstart;	
    td.time = elapsed_seconds.count();
    
    td.matching = mat.card;
    
    return td;
}


int main(int argc, char **argv){
    unsigned int op;
	read_parameters(argc, argv, &op);
    
    unsigned int n, m, s, t;
    
    if(op == 1){
        Graph g;
        read_dimacs_matching_graph(g, cin, &n, &m);
        for(unsigned int i=0;i<NUM_EXP;i++){
            TestData td = hopcroft_karp_test(g);
            printf("%u,%u,%u,%u,%u,%lu,%.2Le,%u\n",i, n, m, td.phases, td.dfsiter, td.mem, td.time, td.matching);
        }
    }else{
        FlowGraph g;
        read_dimacs_flow_matching_graph(g, cin, &n,&m,&s,&t);
        for(unsigned int i=0;i<NUM_EXP;i++){
            size_t mem = memory_used();
            std::chrono::time_point<std::chrono::system_clock> tstart, tend;
            std::chrono::duration<long double> elapsed_seconds;
            tstart = std::chrono::system_clock::now();  
            unsigned int fat = push_relabel_max_flow(g, s, t,
                                                get(&EdgeInformation::edge_capacity,g),
                                                get(&EdgeInformation::edge_residual_capacity,g),
                                                get(&EdgeInformation::reverse_edge,g),
                                                get(boost::vertex_index, g));
            
            tend = std::chrono::system_clock::now();
	        elapsed_seconds = tend-tstart;	
	        printf("%u,%u,%u,0,0,%lu,%.2Le,%u\n",i,n,m,mem,elapsed_seconds.count(),fat);
	    }
	    
    }
	
	return 0;
}

void read_parameters(int argc, char **argv, unsigned int *op){
	
	if(argc < 3){
	    usage(argv);
	    exit(-1);
	}
	
	bool has_op = false;
	
	for(int i=1;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'n':
					i++;
					NUM_EXP = atoi(argv[i]);
					break;
			    case 'o':
			        i++;
			        *op = atoi(argv[i]);
			        has_op = true;
			        break;
				default:
					fprintf(stderr, "Unkown parameter %s \n", argv[i]);
					usage(argv);
					exit(-1);
			}
		}else{
			fprintf(stderr, "Unkown parameter %s \n", argv[i]);
			usage(argv);
			exit(-1);
		}
	}
	
	if(not has_op){
	    usage(argv);
	    exit(-1);
	}
	
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s -o <test option> [-n <number of tests>]\n\t-o test option: \t1 for hopcroft-karp 2 for push-relabel\n\t-n number of tests: \tnatural numbers (default n=10)\n", argv[0]);
}

