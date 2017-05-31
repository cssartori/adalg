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
