#include "../../heap/include/nheap.h"
#include "../include/ffgraph.h"
#include "../include/mem_used.hpp"
#include <vector>
#include <chrono>

using namespace std;
using namespace boost;

//A single flow's path information
struct FlowPath {
    vector<Edge*> path;
    unsigned int flow;
    bool empty;
}; 

// Read a graph in DIMACS format from an input stream. Note that Graph is not guaranteed to be assignable, thus the use of references.
Graph& read_dimacs_max_flow(Graph& g, std::istream& in, unsigned int* n, unsigned int* m, unsigned int* s, unsigned int* t) {
	std::string line="", dummy;
	while (line[0] != 'p' || line[1] != ' ' || line[2] != 'm' || line[3] != 'a' || line[4] != 'x')
        getline(in,line);
 
  	//get nodes and edges
  	sscanf(line.c_str(), "p max %u %u\n", n, m);
    
    //get source and target
    int taken = 0;
    while(taken != 2){
        getline(in,line);
        while (line[0] != 'n')
            getline(in,line);
        
        char which;
        unsigned int k;
        sscanf(line.c_str(), "n %u %c\n", &k, &which);
  	    
  	    if(which == 's')
  	        *s = k-1;
  	    else
  	        *t = k-1;
  	    taken++;
    }
    
    //add vertices to graph g
	for(unsigned int x=0;x<*n;x++)
		add_vertex(g);
  	
  	//read arcs  	
  	unsigned i=0;
  	while (i<*m) {
    	getline(in,line);
    	if (line[0] == 'a' && line[1] == ' ') {
      		unsigned int u,v,c;
      		sscanf(line.c_str(), "a %u %u %u\n", &u, &v, &c);
        	
        	//forward edge	
        	pair<Edge, bool> fep = edge(u-1,v-1,g);
        	if(fep.second){ //edge already exists as reverse edge
        	    g[fep.first].capacity = c;
        	    g[fep.first].residual_capacity += c;
        	}else{ //create new edge    	
          		fep.first = add_edge(u-1,v-1,g).first;
	    		g[fep.first].capacity = c;
	    		g[fep.first].residual_capacity = c;
			}
			
			//reverse edge
           	pair<Edge, bool> rep = edge(v-1,u-1,g);
           	if(!rep.second){ //create new edge
    			rep.first = add_edge(v-1,u-1,g).first;
	    		g[rep.first].residual_capacity = 0;
	        }

			g[fep.first].reverse_edge = rep.first;		
			g[rep.first].reverse_edge = fep.first;

      		i++;
    	}
  	}
 	
  	return g;
}


// Computes the maximum bottleneck flow from s to t in graph g using dijkstra algorithm with max-k-heap 
FlowPath& dijkstra_flow(Graph& g, unsigned int s, unsigned int t, Heap& h, FlowPath& fp){
	//NHeap h(num_vertices(g), k, Heap::MAXHEAP);     //max-k-heap declaration
	vector<unsigned int> fat(num_vertices(g), 0);   //vector with fattest path values

	fat[s] = MAX_FLOW;
    for(unsigned int i=0;i<num_vertices(g);i++)
        h.insert(i, fat[i]);
    
    //FlowPath fp;
    //fp.path = std::vector<Edge>(num_vertices(g));
    fp.empty = false;

	while(!h.is_empty()){
		unsigned int v = h.gettop(); h.deletetop();

		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
			unsigned int u = target(*ie, g);

			if(fat[u] < min(fat[v], g[*ie].residual_capacity)){			    
			    fat[u] = min(fat[v], g[*ie].residual_capacity);
			    h.update_key(u, fat[u]);
			    fp.path[u] = &g[g[*ie].reverse_edge].reverse_edge;	  
			}
		}
	}

	if(fat[t] == 0) //no positive flow in the graph to reach t
	   fp.empty = true;
	   
    fp.flow = fat[t];	
    
	return fp;
}

//Computes the max-flow between nodes s-t in graph g
unsigned int fattest_path(Graph& g, unsigned int s, unsigned int t, unsigned int k){
    unsigned int flow = 0;
    
    NHeap h(num_vertices(g)+1, k, Heap::MAXHEAP);
    
    FlowPath fp;
    fp.path = std::vector<Edge*>(num_vertices(g));
    
    fp = dijkstra_flow(g, s, t, h, fp);

    while(!fp.empty){ //while there is a path between s and t with positive flow
       // printf("Flow of %u : %u\n", fp.flow, flow);
        flow += fp.flow;
        unsigned int v = t;

        while(v != s){ //update the edge's in path with new flow            
            Edge e = *fp.path[v];
            Edge er = g[e].reverse_edge;
                      
            g[e].residual_capacity -= fp.flow;
            g[er].residual_capacity += fp.flow;

           v = source(e, g); //get previous in path
        }
                    
        //get next path
        fp = dijkstra_flow(g, s, t, h, fp);   
    }
        
    return flow;
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

