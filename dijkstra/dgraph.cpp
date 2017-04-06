#include "nheap.h"
#include "dgraph.h"
#include "mem_used.hpp"
#include <vector>

using namespace std;
using namespace boost;


// Read a graph in DIMACS format from an input stream and return a Graph
Graph read_dimacs(std::istream& in, unsigned int* n, unsigned int* m) {
	Graph g;
	std::string line="", dummy;
	while (line.substr(0,4) != "p sp")
    getline(in,line);
 
  	//get nodes and edges
  	std::stringstream linestr;
  	linestr.str(line);
  	linestr >> dummy >> dummy >> *n >> *m;

	for(int x=0;x<*n;x++)
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
      		Edge e = add_edge(u-1,v-1,g).first;
			g[e].weight = w;
      		
      		i++;
    	}
  	}
  	
  	return g;
}

// Computes the shortest path from node s to t in graph g using Dijkstra's algorithm and n-heaps
unsigned int dijkstra_nheap(const Graph& g, unsigned int s, unsigned int t, unsigned int nh){
	NHeap h(nh, num_vertices(g));
	vector<bool> visited(num_vertices(g), false); //no node has been visited yet
	vector<unsigned int> dist(num_vertices(g), MAX_DIST);

	dist[s] = 0;
	h.insert(0, s);
	
	size_t vc = 1;
	while(!h.is_empty()){
		unsigned int v = h.getmin(); h.deletemin();
		visited[v] = true;	

		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
			unsigned int u = target(*ie, g);
			if(!visited[u]){
				if(dist[u] == MAX_DIST){ //distance is "infinity"
					dist[u] = dist[v] +  g[*ie].weight; //update u distance
					h.insert(dist[u], u);
				}else{
					unsigned int ndu = min(dist[u], dist[v]+g[*ie].weight);
					if(ndu < dist[u]){
						h.update_key(u, ndu);
						dist[u] = ndu;
					}
				}
			}
		}
	}
	
	return dist[t];
}


// Computes the shortest path from node s to t in graph g using Dijkstra's algorithm and n-heaps
unsigned int dijkstra_nheap_mem(const Graph& g, unsigned int s, unsigned int t, size_t *mem, unsigned int nh){
	NHeap h(nh, num_vertices(g));
	vector<bool> visited(num_vertices(g), false); //no node has been visited yet
	vector<unsigned int> dist(num_vertices(g), MAX_DIST);

	dist[s] = 0;
	h.insert(0, s);
	*mem = 0;
		
	while(!h.is_empty()){
		unsigned int v = h.getmin(); h.deletemin();
		visited[v] = true;
		*mem = max(*mem, memory_used());	
		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
			unsigned int u = target(*ie, g);
			if(!visited[u]){
				if(dist[u] == MAX_DIST){ //distance is "infinity"
					dist[u] = dist[v] +  g[*ie].weight; //update u distance
					h.insert(dist[u], u);
				}else{
					unsigned int ndu = min(dist[u], dist[v]+g[*ie].weight);
					if(ndu < dist[u]){
						h.update_key(u, ndu);
						dist[u] = ndu;
					}
				}
			}
		}
	}
	
	return dist[t];
}



