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
    Edge edge;
    
    HTreeNode(){
        edge_used = false;
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
vector<HTreeNode> search_paths(const Graph& g, vector<unsigned int>& mates, vector<unsigned int>& v1){
    //TODO: change to queue
    //TODO: use vertex 0 as dummy (maybe)
    //TODO: check how to represent tree H
    //TODO: check how to represent matching M
    //TODO: check how to represent path P
    
    vector<bool> visited(num_vertices(g), false);
    vector<unsigned int> dist(num_vertices(g), 0);
    vector<HTreeNode> h(num_edges(g)); //hungarian tree H
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
			    if(visited[v] == false){
			        dist[v] = dist[u]+1;
			        u2.push(v);
			        h[g[*ie].id].edge_used = true; //mark edge as used in H
			        h[g[*ie].id].edge = *ie;
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
                if(visited[v] == false){
                    dist[v] = dist[u]+1;
                    u1.push(v);
                    Edge e = edge(u,v,g).first;
                    h[g[e].id].edge_used = true;
                    h[g[e].id].edge = e;
                    h[g[e].id].dest = u;
                }
            }
        }
        
    }while(!found); 
    
    return h;
}

bool extract_paths(const Graph& g, vector<unsigned int>& mates, vector<unsigned int> v2, vector<HTreeNode>& h, vector<bool>& matching){
    vector<bool> visited(num_vertices(g), false);
    unsigned int mp = 0;
    
    for(unsigned int i=0;i<v2.size();i++){
        if(mates[v2[i]] != NULL_NODE) continue;
        
        stack<unsigned int> s;
        vector<bool> path(num_edges(g), false);
        s.push(v2[i]);
        
        bool found_path = false;
        while(s.size() > 0 && found_path == false){
            unsigned int u = s.top();
            s.pop();
            if(visited[u]) continue;            
            visited[u] = true;
                        
            printf("Back from node %u\n", u);
            
            graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		    for(tie(ie, fe) = out_edges(u, g); ie != fe; ie++){
    		    unsigned int v = target(*ie, g);
		        if(h[g[*ie].id].edge_used == false || h[g[*ie].id].dest == u) continue;
			    
			    printf("\t%u\n", v);
                //if(v == u) v = source(*ie, g);
                
                if(visited[v] == false){
                    printf("\t\tpushed %u\n", v);
                    s.push(v);
                    path[g[*ie].id] = true;
                    //visited[v] = true;
                    if(v < num_vertices(g)/2 && mates[v] == NULL_NODE){
                       found_path = true;
                       visited[v] = true;
                       break;
                    }
                }  
			}
        }
        
        if(found_path){
            graph_traits<Graph>::edge_iterator ie, fe;  //initial edge iterator and final edge
            for(tie(ie, fe) = edges(g); ie != fe; ie++){
                if(path[g[*ie].id]){
                    if(matching[g[*ie].id]){
                        matching[g[*ie].id] = false;
                        mates[source(*ie,g)] = NULL_NODE;
                        mates[target(*ie,g)] = NULL_NODE;
                    }else{
                        matching[g[*ie].id] = true;
                        mates[source(*ie,g)] = target(*ie,g);
                        mates[target(*ie,g)] = source(*ie,g);                            
                        mp++;
                    }
                }
            }
        }
    }
    
    if(mp != 0)
        return true;
    
    return false;
}

unsigned int hopcroft_karp(const Graph& g){
    
    unsigned int n = num_vertices(g);
    vector<unsigned int> mates(n, NULL_NODE);
    vector<bool> matching(num_edges(g), false);
    
    
    vector<unsigned int> v1(n/2);
    vector<unsigned int> v2(n/2);
    for(int i=0;i<n/2;i++){
        v1[i] = i;
        v2[i] = i+n/2;    
    }
    mates[0] = vertex(5, g);
    mates[5] = vertex(0, g);
    mates[2] = vertex(8, g);
    mates[8] = vertex(2, g);
    mates[3] = vertex(9, g);
    mates[9] = vertex(3, g);
    
//    mates[0] = 5;
//    mates[5] = 0;
//    mates[2] = 6;
//    mates[6] = 2;
//    mates[3] = 9;
//    mates[9] = 3;
//    mates[4] = 8;
//    mates[8] = 4;
    
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
    
    printf("Calling search paths...\n");   
    vector<HTreeNode> h = search_paths(g, mates, v1);
    extract_paths(g, mates, v2, h, matching);
    
    graph_traits<Graph>::edge_iterator ie, fe;  //initial edge iterator and final edge
    for(tie(ie, fe) = edges(g); ie != fe; ie++){
        if(matching[g[*ie].id]){
            printf("e %lu -> %lu\n", source(*ie, g), target(*ie, g));
        }   
    }
    
    return 0;
}


int main(){
    Graph g;
    unsigned int n,m;
    printf("Reading graph...\n");
    read_dimacs_matching_graph(g, cin, &n, &m);
    
    
    printf("Calling hopcroft-karp...\n");
    int h = hopcroft_karp(g);
    
    return 0;
}

