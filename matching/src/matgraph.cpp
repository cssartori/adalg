#include "../include/matgraph.h"
#include "../../heap/include/nheap.h"
#include "../../heap/include/hheap.h"
//#include "../include/mem_used.hpp"
#include <vector>
#include <chrono>

using namespace std;
using namespace boost;

#define graph_traits<Graph>::null_vertex() NULL_NODE

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
      		
      		i++;
    	}
  	}

}

void search_paths(const Graph& g, vector<Node> mates, vector<unsigned int> v1){
    //TODO: change to queue
    //TODO: use vertex 0 as dummy (maybe)
    //TODO: check how to represent tree H
    //TODO: check how to represent matching M
    //TODO: check how to represent path P
    
    vector<bool> visited(num_vertices(g), false);
    vector<unsigned int> dist(num_vertices(g), 0);
    vector<unsigned int> u1, u2;
    for(unsigned int i=0;i<v1.size();i++){
        if(mates[i] == NULL_NODE)
            u1.push_back(i);
    }
    
    bool found = false;
    do{
        //select neighbors in V2 throughout free edges
        while(u1.size() > 0){
            unsigned int u = u1.back();
            visited[u] = true;
            u1.pop_back();
            
            graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		    for(tie(ie, fe) = out_edges(u, g); ie != fe; ie++){
			    unsigned int v = target(*ie, g);
			    if(!visited[v]){
			        dist[v] = dist[u]+1;
			        u2.push_back(v);
			    }
			}
        }
        
        //select neighbors in V1 throughout matched edges
        while(u2.size() > 0){
            unsigned int u = u2.back();
            visited[u] = true;
            u2.pop_back();
            
            if(mates[u] == NULL_NODE){ //free way found
                found = true;
            }else{
                unsigned int v = mates[u];
                if(!visited[v]){
                    dist[v] = dist[u]+1;
                    u1.push_back(v);
                }
            }
        }
        
    }while(!found); 
}

unsigned int hopcroft_karp(const Graph& g){
    
    unsigned int n = num_vertices(g);
    vector<Node> mates(n, NULL_NODE);

    vector<unsigned int> v1(n/2);
    vector<unsigned int> v2(n/2);
    for(int i=0;i<n/2;i++){
        v1[i] = i;
        v2[i] = i+n/2;    
    }
    
    
    
}
