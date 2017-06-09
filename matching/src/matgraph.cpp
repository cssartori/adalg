#include "../include/matgraph.h"
#include <vector>
#include <chrono>
#include <queue>
#include <stack>

using namespace std;
using namespace boost;

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

// Read a graph in DIMACS format from an input stream and return a Graph
void read_dimacs_matching_graph(Graph& g, std::istream& in, unsigned int* n, unsigned int* m) {
	std::string line="", dummy;
	while (line[0] != 'p' || line[1] != ' ' || line[2] != 'e' || line[3] != 'd' || line[4] != 'g' || line[5] != 'e'){
        getline(in,line);
    }
 
  	//get nodes and edges
    sscanf(line.c_str(), "p edge %u %u\n", n, m);
	for(unsigned int x=0;x<*n;x++)
		add_vertex(g);
  	  	
  	unsigned i=0;
  	while (i<*m) {
    	getline(in,line);
    	if (line[0] == 'e' && line[1] == ' ') {
      		unsigned int u,v;
      		sscanf(line.c_str(), "e %u %u\n", &u, &v);
        		
      		Edge e = add_edge(u-1,v-1,g).first;
      		g[e].id = i; //set edge id
      		
      		i++;
    	}
  	}

}


//BFS
bool search_paths(const Graph& g, const vector<unsigned int>& v1, vector<HTreeNode>& h, Matching& mat){    
    vector<bool> visited(num_vertices(g), false);
    //vector<unsigned int> dist(num_vertices(g), 0);
    queue<unsigned int> u1, u2;
    
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
                    Edge e = edge(u,v,g).first;
                    h[g[e].id].edge_used = true;
                    h[g[e].id].dest = u;
                }
            }
        }   
    }while(not found); 
    
    //return wheter a path was found or not
    return found;
}

bool extract_paths(const Graph& g, const vector<unsigned int>& v2, vector<HTreeNode>& h, Matching& mat){
    vector<bool> visited(num_vertices(g), false);
    unsigned int mp = mat.card;
    
    //for each free vertex in v2 run a DFS : TODO: check complexity, should be O(m+n)
    for(unsigned int i=0;i<v2.size();i++){
        if(mat.m[v2[i]] != NULL_NODE) continue;
        
        stack<unsigned int> s;
        stack<Edge> path;
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

unsigned int hopcroft_karp(const Graph& g){
    unsigned int n = num_vertices(g);
    vector<unsigned int> mates(n, NULL_NODE); //vector mates
    vector<HTreeNode> h(num_edges(g)); //hungarian tree H
    Matching mat(num_vertices(g), NULL_NODE); //matching set M
    
    //default definition of vertex sets v1 and v2: v1 U v2 = V : G=(V,E)    
    vector<unsigned int> v1(n/2);
    vector<unsigned int> v2(n/2);
    for(unsigned int i=0;i<n/2;i++){
        v1[i] = i;
        v2[i] = i+n/2;    
    }   
    
    //the main loop of the algorithm
    int phases = 0;      
    while(search_paths(g, v1, h, mat)){
        bool has_extract = extract_paths(g, v2, h, mat);
        if(not has_extract)
            break;           
        for(unsigned int i=0;i<h.size();i++)
            h[i].edge_used = false;
         
        phases++;
    }
    
    return mat.card;
}

