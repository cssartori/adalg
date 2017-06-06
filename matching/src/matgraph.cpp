#include "../include/matgraph.h"
#include "../../heap/include/nheap.h"
#include "../../heap/include/hheap.h"
//#include "../include/mem_used.hpp"
#include <vector>
#include <chrono>
#include <queue>
#include <stack>

using namespace std;
using namespace boost;

#define NULL_NODE num_vertices(g)+1

struct HTreeNode{
    bool edge_used;
    unsigned int dest;
    
    HTreeNode(){
        edge_used = false;
    }
};

struct Matching{
    unsigned int card; //set cardinality
    vector<bool> m;
    
    Matching(unsigned int sz){
        card = 0;
        m.assign(sz, false);
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
bool search_paths(const Graph& g, const vector<unsigned int>& v1, const vector<unsigned int>& mates, vector<HTreeNode>& h){
    //TODO: change to queue
    //TODO: use vertex 0 as dummy (maybe)
    //TODO: check how to represent tree H
    //TODO: check how to represent matching M
    //TODO: check how to represent path P
    
    vector<bool> visited(num_vertices(g), false);
    vector<unsigned int> dist(num_vertices(g), 0);
    queue<unsigned int> u1, u2;
    for(unsigned int i=0;i<v1.size();i++){
        if(mates[i] == NULL_NODE)
            u1.push(i);
    }
    
    bool found = false;
    do{
    
        if(u1.size() == 0)
            break;
        //select neighbors in V2 throughout free edges    
        while(u1.size() > 0){
            unsigned int u = u1.front();
            visited[u] = true;
            u1.pop();
            
            graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		    for(tie(ie, fe) = out_edges(u, g); ie != fe; ie++){
			    unsigned int v = target(*ie, g);
			    if(not visited[v]){
			        dist[v] = dist[u]+1;
			        u2.push(v);
			        h[g[*ie].id].edge_used = true; //mark edge as used in H
			        h[g[*ie].id].dest = u;
			    }
			}
        }
        
        if(u2.size() == 0)
            break;
        //select neighbors in V1 throughout matched edges
        while(u2.size() > 0){
            unsigned int u = u2.front();
            visited[u] = true;
            u2.pop();
            
            if(mates[u] == NULL_NODE){ //free way found
                found = true;
            }else{
                unsigned int v = mates[u];
                if(not visited[v]){
                    dist[v] = dist[u]+1;
                    u1.push(v);
                    Edge e = edge(u,v,g).first;
                    h[g[e].id].edge_used = true;
                    h[g[e].id].dest = u;
                }
            }
        }
        
    }while(not found); 
    
    return found;
}

bool extract_paths(const Graph& g, const vector<unsigned int>& v2, vector<unsigned int>& mates, vector<HTreeNode>& h, Matching& mat){
    vector<bool> visited(num_vertices(g), false);
    unsigned int mp = mat.card;
    
    for(unsigned int i=0;i<v2.size();i++){
        if(mates[v2[i]] != NULL_NODE) continue;
        
        stack<unsigned int> s;
        stack<Edge> path;
        s.push(v2[i]);
        
        bool found_path = false;
        while(s.size() > 0 && not found_path){
            unsigned int u = s.top();
            s.pop();
            if(visited[u]) continue;            
            visited[u] = true;

            graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		    for(tie(ie, fe) = out_edges(u, g); ie != fe; ie++){
    		    unsigned int v = target(*ie, g);
		        if( not h[g[*ie].id].edge_used || h[g[*ie].id].dest == u) continue;
                
                if(not visited[v]){
                    s.push(v);
                    path.push(*ie);
                    if(mates[v] == NULL_NODE){ //if v is free, then it is in V1 and we found what we wanted
                       found_path = true;   //set that a path has been found
                       visited[v] = true;   //mark node v as visited so that it is not used in another path
                       break; //a valid path has been found, stop search
                    }
                }  
			}
        }
        
        if(found_path){         
            bool origin_found = false;
            unsigned int back = target(path.top(), g);
            while(!origin_found){
                Edge e = path.top();
                path.pop();
                
                if(back != target(e, g)) continue;
                
                back = source(e,g);
                if(source(e, g) == v2[i] || target(e, g) == v2[i]){
                    origin_found = true;
                    //printf("Origin found and path size is %u\n", path.size());
                    }
                
                    if(mat.m[g[e].id]){
                        mat.m[g[e].id] = false;
                        mat.card -= 1;
                    }else{
                        mat.m[g[e].id] = true;
                        mates[source(e,g)] = target(e,g);
                        mates[target(e,g)] = source(e,g);                            
                        mat.card += 1;
                    }
                
            }
//            printf("==========\n");
        }
    }
    
    //mat.card += mp;
    
    if(mp < mat.card)
        return true;
    
    return false;
}

unsigned int hopcroft_karp(const Graph& g){
    
    unsigned int n = num_vertices(g);
    vector<unsigned int> mates(n, NULL_NODE); //vector mates
    vector<HTreeNode> h(num_edges(g)); //hungarian tree H
    Matching mat(num_edges(g)); //matching set M
        
    vector<unsigned int> v1(n/2);
    vector<unsigned int> v2(n/2);
    for(int i=0;i<n/2;i++){
        v1[i] = i;
        v2[i] = i+n/2;    
    }

//    mates[0] = vertex(5, g);
//    mates[5] = vertex(0, g);
//    mates[2] = vertex(8, g);
//    mates[8] = vertex(2, g);
//    mates[3] = vertex(9, g);
//    mates[9] = vertex(3, g);
    
//    matching[g[edge(3,9,g).first].id] = true;
//    matching[g[edge(2,8,g).first].id] = true;
//    matching[g[edge(0,5,g).first].id] = true;
    
//    mates[0] = 5;
//    mates[5] = 0;
//    mates[2] = 6;
//    mates[6] = 2;
//    mates[3] = 9;
//    mates[9] = 3;
//    mates[4] = 8;
//    mates[8] = 4;
//    
//        matching[g[edge(4,8,g).first].id] = true;
//    matching[g[edge(3,9,g).first].id] = true;
//    matching[g[edge(0,5,g).first].id] = true;
//            matching[g[edge(2,6,g).first].id] = true;
    
//    mates[0] = 9;
//    mates[9] = 0;
//    mates[1] = 5;
//    mates[5] = 1;
//    mates[2] = 7;
//    mates[7] = 2;
//    mates[3] = 6;
//    mates[6] = 3;
//    mates[4] = 8;
//    mates[8] = 4;
    
    
    int phases = 0;      
    while(search_paths(g, v1, mates, h)){
        if(extract_paths(g, v2, mates, h, mat)){
            for(unsigned int i=0;i<h.size();i++){
                h[i].edge_used = false;
            }    
        }
         
        phases++;
    }
    
//    int ii=0;
//    graph_traits<Graph>::edge_iterator ie, fe;  //initial edge iterator and final edge
//    for(tie(ie, fe) = edges(g); ie != fe; ie++){
//        if(mat.m[g[*ie].id]){
//            printf("%i %lu -> %lu\n", ii++, source(*ie, g), target(*ie, g));
//        }   
//    }
    
    printf("phases = %u | sqrt(n) = %.2f\n", phases, sqrt(n));
    
    return mat.card;
}


//int main(){
//    Graph g;
//    unsigned int n,m;
//    printf("Reading graph...\n");
//    read_dimacs_matching_graph(g, cin, &n, &m);
//    
//    
//    printf("Calling hopcroft-karp...\n");
//    int h = hopcroft_karp(g);
//    
//    return 0;
//}

