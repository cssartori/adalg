#include "../../heap/include/nheap.h"
#include "../include/dgraph.h"
#include "../include/mem_used.hpp"
#include <vector>
#include <chrono>

using namespace std;
using namespace boost;


// Read a graph in DIMACS format from an input stream and return a Graph
Graph read_dimacs_max_flow(std::istream& in, unsigned int* n, unsigned int* m, unsigned int* s, unsigned int* t) {
	Graph g;
	std::string line="", dummy;
	while (line.substr(0,5) != "p max")
        getline(in,line);
 
  	//get nodes and edges
  	std::stringstream linestr;
  	linestr.str(line);
  	linestr >> dummy >> dummy >> *n >> *m;
    
    //get source and target
    int taken = 0;
    while(taken != 2){
        line="";
        while (line[0] != 'n')
            getline(in,line);
        
        char which;
        unsigned int k;
        char dm;
        std::stringstream lstr;
        lstr.str(line);
  	    lstr >> dm >> k >> which;
  	    
  	    if(which == 's')
  	        *s = k-1;
  	    else
  	        *t = k-1;
  	    taken++;
    }
    
    printf("adding %u vertices\n", *n);
    //add vertices to graph g
	for(unsigned int x=0;x<*n;x++)
		add_vertex(g);
  	
  	//read arcs  	
  	unsigned i=0;
  	while (i<*m) {
    	getline(in,line);
    	if (line.substr(0,2) == "a ") {
      		std::stringstream arc(line);
      		unsigned int u,v,c;
      		char ac;
      		arc >> ac >> u >> v >> c;
        		
        	//forward edge	
      		Edge e = add_edge(u-1,v-1,g).first;
			g[e].capacity = c;
			g[e].residual_capacity = c;
			
			
			//reverse edge
			EdgeData *er = new EdgeData;
			er->capacity = c;
			er->residual_capacity = c;
			er->reverse_edge = &g[e];
      		
      		g[e].reverse_edge = er;
      		i++;
    	}
  	}
  	
  	return g;
}

// Computes the shortest path from node s to t in graph g using Dijkstra's algorithm and n-heaps
unsigned int dijkstra_nheap(const Graph& g, unsigned int s, unsigned int t, unsigned int nh){
    printf("Creating heap...\n");
	NHeap h(num_vertices(g), nh, Heap::MAXHEAP);
	//vector<bool> visited(num_vertices(g), false); //no node has been visited yet
	printf("Allocating fat vector with %u...\n", num_vertices(g));
	vector<unsigned int> fat(num_vertices(g), 0);
	printf("fat = { ");
	for(int i =0;i<num_vertices(g);i++)
	    printf("%u, ", fat[i]);
	
	printf("}\n");
    printf("Setting fat[s] = inf\n");
	fat[s] = MAX_DIST;
    
    printf("Inserting all vertices in heap...\n");
    for(unsigned int i=0;i<num_vertices(g);i++)
        h.insert(i, fat[i]);
	
	printf("Main loop:\n");
	while(!h.is_empty()){
		unsigned int v = h.gettop(); h.deletetop();
        printf("\tremoved vertex %u\n", v);
		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
			unsigned int u = target(*ie, g);
			Edge e = edge(v,u,g).first;
//			printf("%i = e.b\n", e.second);
//			//Edge e;
//		    printf("\t\tneighbor %u\n", u);
//			printf("%u < min(", fat[u]);
//			printf("%u,", fat[v]);
//			printf("%u)\n", g[e.first].capacity);
			if(fat[u] < min(fat[v], g[e].capacity)){
			    
			    fat[u] = min(fat[v], g[e].capacity);
			    h.update_key(u, fat[u]);	
			}
		}
	}
	
	return fat[t];
}

//// Implementation of Dijkstra's algorithm with n-heaps for testing purposes (collects memory used, number of insertions, deletions, updates and execution time)
//unsigned int dijkstra_nheap_test(const Graph& g, unsigned int s, unsigned int t, unsigned int *n_ins, unsigned int *n_del, unsigned int *n_upd, long double *time, size_t *mem, unsigned int nh){

//	NHeap h(num_vertices(g), nh);
//	std::chrono::time_point<std::chrono::system_clock> tstart, tend;
//    std::chrono::duration<long double> elapsed_seconds;
//	vector<bool> visited(num_vertices(g), false); //no node has been visited yet
//	vector<unsigned int> dist(num_vertices(g), MAX_DIST);
//	*n_ins = 0;
//	*n_del = 0;
//	*n_upd = 0;

//	dist[s] = 0;
//	h.insert(s, 0); 
//	*n_ins += 1;
//	
//	if(mem != NULL)
//		*mem = memory_used(); //all memory is allocated up to this point	
//	
//	tstart = std::chrono::system_clock::now();
//		
//	while(!h.is_empty()){
//		unsigned int v = h.getmin(); h.deletemin();
//		*n_del += 1;
//		visited[v] = true;
//		
//		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
//		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
//			unsigned int u = target(*ie, g);
//			if(!visited[u]){
//				if(dist[u] == MAX_DIST){ //distance is "infinity"
//					dist[u] = dist[v] +  g[*ie].weight; //update u distance
//					h.insert(u, dist[u]);
//					*n_ins += 1;
//				}else{
//					unsigned int ndu = min(dist[u], dist[v]+g[*ie].weight);
//					if(ndu < dist[u]){
//						h.decrease_key(u, ndu);
//						dist[u] = ndu;
//						*n_upd += 1;
//					}
//				}
//			}
//		}
//	}
//	
//	tend = std::chrono::system_clock::now();
//	elapsed_seconds = tend-tstart;	
//	*time = elapsed_seconds.count();
//	
//	return dist[t];
//}


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

