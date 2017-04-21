#include "../include/nheap.h"
#include "../include/dgraph.h"
#include "../include/mem_used.hpp"
#include "../include/hheap.hpp"
#include <vector>
#include <chrono>

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

	for(unsigned int x=0;x<*n;x++)
		add_vertex(g);
  	  	
  	unsigned i=0;
  	while (i<*m) {
    	getline(in,line);
    	if (line.substr(0,2) == "a ") {
      		std::stringstream arc(line);
      		unsigned int u,v,w;
      		char ac;
      		arc >> ac >> u >> v >> w;
        		
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

// Implementation of Dijkstra's algorithm with n-heaps for testing purposes (collects memory used, number of insertions, deletions, updates and execution time)
unsigned int dijkstra_nheap_test(const Graph& g, unsigned int s, unsigned int t, unsigned int *n_ins, unsigned int *n_del, unsigned int *n_upd, long double *time, size_t *mem, unsigned int nh){

	NHeap h(nh, num_vertices(g));
	std::chrono::time_point<std::chrono::system_clock> tstart, tend;
    std::chrono::duration<long double> elapsed_seconds;
	vector<bool> visited(num_vertices(g), false); //no node has been visited yet
	vector<unsigned int> dist(num_vertices(g), MAX_DIST);
	*n_ins = 0;
	*n_del = 0;
	*n_upd = 0;

	dist[s] = 0;
	h.insert(0, s); 
	*n_ins += 1;
	
	if(mem != NULL)
		*mem = memory_used(); //all memory is allocated up to this point	
	
	tstart = std::chrono::system_clock::now();
		
	while(!h.is_empty()){
		unsigned int v = h.getmin(); h.deletemin();
		*n_del += 1;
		visited[v] = true;
		
		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
			unsigned int u = target(*ie, g);
			if(!visited[u]){
				if(dist[u] == MAX_DIST){ //distance is "infinity"
					dist[u] = dist[v] +  g[*ie].weight; //update u distance
					h.insert(dist[u], u);
					*n_ins += 1;
				}else{
					unsigned int ndu = min(dist[u], dist[v]+g[*ie].weight);
					if(ndu < dist[u]){
						h.update_key(u, ndu);
						dist[u] = ndu;
						*n_upd += 1;
					}
				}
			}
		}
	}
	
	tend = std::chrono::system_clock::now();
	elapsed_seconds = tend-tstart;	
	*time = elapsed_seconds.count();
	
	return dist[t];
}

// Computes the shortest path from node s to t in graph g using Dijkstra's algorithm and n-heaps
unsigned int dijkstra_hheap(const Graph& g, unsigned int s, unsigned int t, unsigned int nh){
	HHeap h;
	vector<bool> visited(num_vertices(g), false); //no node has been visited yet
	vector<unsigned int> dist(num_vertices(g), MAX_DIST);

	dist[s] = 0;
	h.insert(s, 0);
	
	while(!h.is_empty()){
		unsigned int v = h.getmin(); h.deletemin();
		visited[v] = true;	

		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
			unsigned int u = target(*ie, g);
			if(!visited[u]){
				if(dist[u] == MAX_DIST){ //distance is "infinity"
					dist[u] = dist[v] +  g[*ie].weight; //update u distance
					h.insert(u, dist[u]);
				}else{
					unsigned int ndu = min(dist[u], dist[v]+g[*ie].weight);
					if(ndu < dist[u]){
						h.decrease_key(u, ndu);
						dist[u] = ndu;
					}
				}
			}
		}
	}

	return dist[t];
}

//Returns true if edge between node u and v exists
bool edge_exist(const Graph& g, unsigned int u, unsigned int v){
	
	graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
	for(tie(ie, fe) = out_edges(u, g); ie != fe; ie++){
		unsigned int t = target(*ie, g);
		if(v == t)
			return true;
	}
			
	return false;
}

