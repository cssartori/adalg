#include "../../heap/include/nheap.h"
#include "../include/ffgraph.h"
#include "../include/mem_used.hpp"
#include "../../common/cc_gv.h"
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
    
    //gv_init("graph.gr");
    
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
	for(unsigned int x=0;x<*n;x++){
		add_vertex(g);
		//gv_declare(x);
    }
  	
  	//read arcs  	
  	unsigned i=0;
  	while (i<*m) {
    	getline(in,line);
    	if (line[0] == 'a' && line[1] == ' ') {
      		unsigned int u,v,c;
      		sscanf(line.c_str(), "a %u %u %u\n", &u, &v, &c);
        	
        	//gv_connect(u-1,v-1,c);
        	
        	//forward edge	
        	pair<Edge, bool> fep;
        	fep.first = add_edge(u-1,v-1,g).first;
    		g[fep.first].capacity = c;
    		g[fep.first].residual_capacity = c;
    		
    		//code comment to be used only when backwards edges are allowed in the input data
//        	pair<Edge, bool> fep = edge(u-1,v-1,g);
//        	if(fep.second){ //edge already exists as reverse edge
//        	    g[fep.first].capacity = c;
//        	    g[fep.first].residual_capacity += c;
//        	}else{ //create new edge    	
//          	fep.first = add_edge(u-1,v-1,g).first;
//	    		g[fep.first].capacity = c;
//	    		g[fep.first].residual_capacity = c;
//			}
			
			//reverse edge
			pair<Edge, bool> rep;
			rep.first = add_edge(v-1,u-1,g).first;
	    	g[rep.first].residual_capacity = 0;
	    	
//         	pair<Edge, bool> rep = edge(v-1,u-1,g);
//         	if(!rep.second){ //create new edge
//   			rep.first = add_edge(v-1,u-1,g).first;
//	    		g[rep.first].residual_capacity = 0;
//	        }

			g[fep.first].reverse_edge = rep.first;		
			g[rep.first].reverse_edge = fep.first;

      		i++;
    	}
  	}
 	
 	//gv_close();
 	//printf("Finshed reading...\n");
  	return g;
}


// Computes the maximum bottleneck flow from s to t in graph g using dijkstra algorithm with max-k-heap 
FlowPath& dijkstra_flow(Graph& g, unsigned int s, unsigned int t, Heap& h, FlowPath& fp){
	
	vector<unsigned int> fat(num_vertices(g), 0);   //vector with fattest path values
    vector<unsigned int> visited(num_vertices(g), false); //vector of visited nodes
    
	fat[s] = MAX_FLOW;
    h.insert(s, fat[s]);
    
    fp.empty = false;

	while(!h.is_empty()){
		unsigned int v = h.gettop(); h.deletetop();
       	visited[v] = true;
		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
			unsigned int u = target(*ie, g);
            if(!visited[u]){
                if(fat[u] == 0){
                    fat[u] = min(fat[v], g[*ie].residual_capacity);
                    h.insert(u,fat[u]);
                    fp.path[u] = &g[g[*ie].reverse_edge].reverse_edge;
                }else if(fat[u] < min(fat[v], g[*ie].residual_capacity)){			    
			        fat[u] = min(fat[v], g[*ie].residual_capacity);
			        h.update_key(u, fat[u]);
			        fp.path[u] = &g[g[*ie].reverse_edge].reverse_edge;	  
			    }
			}
		}
		if(v == t){
		    while(!h.is_empty())
		        h.deletetop();		        
		    break;
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
FlowPath& dijkstra_flow_test(Graph& g, unsigned int s, unsigned int t, Heap& h, FlowPath& fp, TestData& td, bool get_mem=false){    

	vector<unsigned int> fat(num_vertices(g), 0);   //vector with fattest path values
    vector<unsigned int> visited(num_vertices(g), false); //vector of visited nodes
    
	fat[s] = MAX_FLOW;
    h.insert(s, fat[s]);
    td.nins += 1;
    
    fp.empty = false;
    
    if(get_mem)
        td.mem = max(td.mem, memory_used());
    
	while(!h.is_empty()){
		unsigned int v = h.gettop(); h.deletetop();
       	visited[v] = true;
       	td.ndel += 1;
		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, g); ie != fe; ie++){
			unsigned int u = target(*ie, g);
            if(!visited[u]){
                if(fat[u] == 0){
                    fat[u] = min(fat[v], g[*ie].residual_capacity);
                    h.insert(u,fat[u]);
                    td.nins += 1;
                    fp.path[u] = &g[g[*ie].reverse_edge].reverse_edge;
                }else if(fat[u] < min(fat[v], g[*ie].residual_capacity)){			    
			        fat[u] = min(fat[v], g[*ie].residual_capacity);
			        h.update_key(u, fat[u]);
			        td.nupd += 1;
			        fp.path[u] = &g[g[*ie].reverse_edge].reverse_edge;	  
			    }
			}
		}
		if(v == t){
		    while(!h.is_empty())
		        h.deletetop();		        
		    break;
		}
	}


	if(fat[t] == 0) //no positive flow in the graph to reach t
	   fp.empty = true;
	   
    fp.flow = fat[t];	
    
	return fp;
}

//Computes the max-flow between nodes s-t in graph g. Used for testing purposes. 
//(stores the number of calls to dijkstra algorithm, number of heap inserts, deletes and updates, as well as memmory consumption).
TestData fattest_path_test(Graph& g, unsigned int s, unsigned int t, unsigned int k){
    std::chrono::time_point<std::chrono::system_clock> tstart, tend;
    std::chrono::duration<long double> elapsed_seconds;
    tstart = std::chrono::system_clock::now();    
    
    unsigned int flow = 0;    
    TestData td;
    td.ndij = 0;
    td.nins = 0;
    td.ndel = 0;
    td.nupd = 0;
    td.nswp = 0;
    td.nitr = 0;
    td.time = 0;
    td.mem = 0;
    td.flow = 0;
    
    NHeap h(num_vertices(g)+1, k, Heap::MAXHEAP);
    
    FlowPath fp;
    fp.path = std::vector<Edge*>(num_vertices(g));
    
    fp = dijkstra_flow_test(g, s, t, h, fp, td, true);
    td.ndij += 1;

    while(!fp.empty){ //while there is a path between s and t with positive flow
        td.nitr += 1;
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
        td.ndij += 1;
    }
    
    tend = std::chrono::system_clock::now();
	elapsed_seconds = tend-tstart;	
    td.time = elapsed_seconds.count();
    td.flow = flow;
    td.nswp = h.n_swaps;
        
    return td;
}

