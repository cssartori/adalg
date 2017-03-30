#include "nheap.h"
#include <cstdio>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;
 using namespace std;
 
//a vertex's data
typedef struct {
  unsigned int v;
} VertexData;
 
//an edge's data
typedef struct  {
  unsigned int weight; //weight is only positive for dijkstra
} EdgeData;
 
 
//A graph is an adjacency list represented by vectors (vecS)
typedef adjacency_list<vecS, vecS, directedS, VertexData, EdgeData> Graph;
typedef graph_traits<Graph>::vertex_descriptor Node;
typedef graph_traits <Graph>::edge_descriptor Edge;
 




Graph read_dimacs(std::istream& in, unsigned int* n, unsigned int* m) {
	Graph g;
	std::string line="", dummy;
	while (line.substr(0,4) != "p sp")
    getline(in,line);
 
  	//get nodes and edges
  	std::stringstream linestr;
  	linestr.str(line);
  	linestr >> dummy >> dummy >> *n >> *m;
  	
  	for(unsigned int i=0; i<*n ; i++)
    	add_vertex(g);
  	
  	unsigned i=0;
  	while (i<*m) {
    	getline(in,line);
    	if (line.substr(0,2) == "a ") {
      		std::stringstream arc(line);
      		unsigned int u,v,w;
      		char ac;
      		arc >> ac >> u >> v >> w;
     		// process arc (u,v) with weight w      		
      		Edge e = add_edge(u,v,g).first;
			g[e].weight = w;
      		
      		i++;
    	}
  	}
  	
  	return g;
}



int main(int argc, char **argv){
	if(argc < 3){
		printf("Usage: %s [source node] [target node]\n", argv[0]);
		return 0;
	}
	
	//source and target nodes
	int s = atoi(argv[1]);
	int t = atoi(argv[2]);
	
	unsigned int n, m;
		
	Graph g = read_dimacs(std::cin, &n, &m);
	
 	graph_traits<Graph>::edge_iterator eb, ee;
 	for ( tie(eb, ee)=edges(g); eb != ee; eb++)
    	cout << "a " << source(*eb,g) << " " << target(*eb, g) << " " << g[*eb].weight << endl;
 		
	return 0;
}
