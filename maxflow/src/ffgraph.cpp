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

//Data to be collected when testing
struct TestData {
    unsigned int *ndij; //number of calls to dijkstra
    unsigned int *nins; //number of inserts in heap
    unsigned int *ndel; //number of deletes in heap
    unsigned int *nupd; //number of updates in heap
    long double *time; //time to execute the algorithm
    size_t *mem; //amount of memory used
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
	vector<unsigned int> fat(num_vertices(g), 0);   //vector with fattest path values

	fat[s] = MAX_FLOW;
    for(unsigned int i=0;i<num_vertices(g);i++)
        h.insert(i, fat[i]);
    
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

// Computes the maximum bottleneck flow from s to t in graph g using dijkstra algorithm with max-k-heap 
FlowPath& dijkstra_flow_test(Graph& g, unsigned int s, unsigned int t, Heap& h, FlowPath& fp, TestData& td){    
	vector<unsigned int> fat(num_vertices(g), 0);   //vector with fattest path values

	fat[s] = MAX_FLOW;
    for(unsigned int i=0;i<num_vertices(g);i++){
        h.insert(i, fat[i]);
        *td.nins += 1;
    }
    
    if(td.mem != NULL)
        *td.mem = max(*td.mem, memory_used());
    
    fp.empty = false;

	while(!h.is_empty()){
		unsigned int v = h.gettop(); h.deletetop();
        *td.ndel += 1;
        
		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
			unsigned int u = target(*ie, g);

			if(fat[u] < min(fat[v], g[*ie].residual_capacity)){			    
			    fat[u] = min(fat[v], g[*ie].residual_capacity);
			    h.update_key(u, fat[u]);
			    fp.path[u] = &g[g[*ie].reverse_edge].reverse_edge;	  
			    *td.nupd += 1;
			}
		}
	}

	if(fat[t] == 0) //no positive flow in the graph to reach t
	   fp.empty = true;
	   
    fp.flow = fat[t];	
    
	return fp;
}

//Computes the max-flow between nodes s-t in graph g. Used for testing purposes. 
//(stores the number of calls to dijkstra algorithm, number of heap inserts, deletes and updates, as well as memmory consumption).
unsigned int fattest_path_test(Graph& g, unsigned int s, unsigned int t, unsigned int *ndij, unsigned int *nins, unsigned int *ndel, unsigned int *nupd, long double *time, size_t *mem, unsigned int k){
    std::chrono::time_point<std::chrono::system_clock> tstart, tend;
    std::chrono::duration<long double> elapsed_seconds;
    tstart = std::chrono::system_clock::now();    
    
    unsigned int flow = 0;
    *ndij = 0;
    *nins = 0;
    *ndel = 0;
    *nupd = 0;
    *time = 0;
    *mem = 0;
    
    TestData td;
    td.ndij = ndij;
    td.nins = nins;
    td.ndel = ndel;
    td.nupd = nupd;
    td.time = time;
    td.mem = mem;
    
    NHeap h(num_vertices(g)+1, k, Heap::MAXHEAP);
    
    FlowPath fp;
    fp.path = std::vector<Edge*>(num_vertices(g));
    
    fp = dijkstra_flow_test(g, s, t, h, fp, td);
    *td.ndij += 1;
    td.mem = NULL; //avoid delaying the testing. One measure is enough for most cases.

    while(!fp.empty){ //while there is a path between s and t with positive flow
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
        fp = dijkstra_flow_test(g, s, t, h, fp, td);   
        *td.ndij += 1;
    }
    
    tend = std::chrono::system_clock::now();
	elapsed_seconds = tend-tstart;	
    *td.time = elapsed_seconds.count();
//	*ndij = *td.ndij;
//	*nins = *td.nins;
//	*ndel = *td.ndel;
//	*nupd = *td.nupd;
//	*time = elapsed_seconds.count();
        
    return flow;
}
