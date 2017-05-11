#include "../../heap/include/nheap.h"
#include "../include/dgraph.h"
#include "../include/mem_used.hpp"
#include <vector>
#include <chrono>

using namespace std;
using namespace boost;

struct FlowPath {
    vector<Edge> path;
    unsigned int flow;
    bool empty;
}; 

Graph gr;

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
    
    //add vertices to graph g
	for(unsigned int x=0;x<*n;x++)
		add_vertex(gr);
  	
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
        	pair<Edge, bool> fep = add_edge(u-1,v-1,gr);
        	if(!fep.second){ //edge already exists as reverse edge
        	    gr[fep.first].capacity = c;
        	    gr[fep.first].residual_capacity += c;
        	}else{ //create new edge    	
        	   //            	    cout << "Creating new edge  between " << u-1 << " -> " << v-1 << endl;
          		//Edge e = add_edge(u-1,v-1,g).first;
	    		gr[fep.first].capacity = c;
	    		gr[fep.first].residual_capacity = c;
			}
			
			//reverse edge
           	pair<Edge, bool> rep = add_edge(v-1,u-1,gr);
           	if(rep.second){ //create new edge
           	 //   cout << "Creating new edge  between " << v-1 << " -> " << u-1 << endl;
    			//Edge er = add_edge(v-1,u-1,g).first;
	    		gr[rep.first].residual_capacity = 0;
	    		//rep.first = er;
	        }
			//printf("edge %u -> %u\n", u-1, v-1);
			//cout << "rep = " << rep.first << " fep = " << fep.first << endl;
//			printf("rep = %lu | erp = %lu\n", rep.first, edge(v-1,u-1,g).first);
			gr[fep.first].reverse_edge = rep.first;
			
//			cout << "first done...\n";
//			cout << "g[fep] = " << g[fep.first].reverse_edge << "  r = " << g[g[fep.first].reverse_edge].reverse_edge << "  rp = " << rep.first << endl;
//			printf("  rep = %lu | %lu\n", rep.first, g[fep.first].reverse_edge);			
			gr[rep.first].reverse_edge = fep.first;
			//cout << "g[].rev = " << gr[fep.first].reverse_edge << " rep = " << rep.first << " g[g[].rev].rev = " << gr[gr[fep.first].reverse_edge].reverse_edge << endl;
			
		//	cout << "fep == g[g[f].rev].rev : " << (fep.first == gr[gr[fep.first].reverse_edge].reverse_edge) << endl;
			//cout << "fep == g[r].rev : " << (fep.first == gr[rep.first].reverse_edge) << endl;
			
//			cout << "g[rep] = " << g[rep.first].reverse_edge;
//			printf("  rep = %lu | %lu\n", rep.first, g[rep.first].reverse_edge);
			
			//printf("r: %u -> %u | %u -> %u [%u, %u]\n", u-1, v-1, &(g[fep.first].reverse_edge), &(g[rep.first].reverse_edge), g[fep.first].residual_capacity, g[rep.first].residual_capacity/*source(fep.first, g), target(fep.first, g)*/);
      		i++;
    	}
  	}
  	
//  	graph_traits<Graph>::edge_iterator ie, fe;
//  	for(tie(ie, fe) = edges(g); ie != fe; ie++){
//  	    printf("%u -> %u [%u,%u]\n", source(*ie, g), target(*ie, g), g[*ie].residual_capacity, g[g[*ie].reverse_edge].residual_capacity);
//  	}
  	
  	g = gr;
  	//exit(-1);
  	return g;
}


// Computes the maximum bottleneck flow from s to t in graph g using dijkstra algorithm with max-k-heap 
FlowPath dijkstra_flow(const Graph& g, unsigned int s, unsigned int t, unsigned int k=2){
	NHeap h(num_vertices(gr), k, Heap::MAXHEAP);     //max-k-heap declaration
	vector<unsigned int> fat(num_vertices(gr), 0);   //vector with fattest path values

	fat[s] = MAX_FAT;

    for(unsigned int i=0;i<num_vertices(gr);i++)
        h.insert(i, fat[i]);
    
    //printf("DF :: &(2->3) = %u\n", &(g[edge(3,2,g).first].reverse_edge));
    
    FlowPath fp;//=new FlowPath; 
    fp.path = std::vector<Edge>(num_vertices(gr));
    
    fp.empty = false;
    unsigned int pt = t;
	while(!h.is_empty()){
		unsigned int v = h.gettop(); h.deletetop();

		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(v, gr); ie != fe; ie++){
			unsigned int u = target(*ie, gr);
          //  printf("**%lu -> %u\n", source(*ie, g), u);
			if(fat[u] < min(fat[v], gr[*ie].residual_capacity)/* && g[e].residual_capacity > 0*/){			    
			    fat[u] = min(fat[v], gr[*ie].residual_capacity);
			    h.update_key(u, fat[u]);
			    fp.path[u] = gr[gr[*ie].reverse_edge].reverse_edge;
			 //   printf("fp[u] = %lu ", fp.path[u]);
			   // cout << "   *fp[u] = " << fp.path[u] << endl;
			    //Edge k = fp.path[u];
			   // printf("%u -> %u : %u (%u) | %u -> %u\n", v, u, fp.path[u],(k), source(k,g), target(k,g));
			  //  cout << "EDGE = " << k << " | FP = " << fp.path[u] << " | " << source(k,g) << " -> " << target(k, g) << " | " << g[k].reverse_edge <<  endl;	
			  //  printf("+%u -> %u\n", source(g[*ie].reverse_edge, g), target(g[*ie].reverse_edge, g));
			  //  printf("*%lu -> %lu | %lu -> %lu\n", source(*(fp.path[u]), g), target(*fp.path[u], g), source(g[g[*ie].reverse_edge].reverse_edge, g), target(g[g[*ie].reverse_edge].reverse_edge, g));		  
			}
		}
		if(v == t) //already reached t
		    break;
	}
	//cout << "fp.empty = " << (fat[t] == 0) << endl;
	if(fat[t] == 0) //no positive flow in the graph to reach t
	   fp.empty = true;
	//exit(-1);
    fp.flow = fat[t];	
    //cout << "ret fp" << endl;
	return fp;
}


unsigned int fattest_path(Graph& g, unsigned int s, unsigned int t, unsigned int k){
    unsigned int flow = 0;
       
    FlowPath fp = dijkstra_flow(gr, s, t, k);
        //printf("FT :: &(2->3) = %u\n", &(g[edge(3,2,g).first].reverse_edge));
        
//      	graph_traits<Graph>::edge_iterator ie, fe;
//  	for(tie(ie, fe) = edges(gr); ie != fe; ie++){
//  	   cout << "E = " << *ie << " ER = " << gr[*ie].reverse_edge << " ERR = " << gr[gr[*ie].reverse_edge].reverse_edge << " | E == ERR : " << (*ie == gr[gr[*ie].reverse_edge].reverse_edge) << endl;
//  	   printf ("\tE = %lu | ER = %lu | ERR = %lu\n", *ie, gr[*ie].reverse_edge, gr[gr[*ie].reverse_edge].reverse_edge);
//  	}    
        
    int c = 0;
    while(!fp.empty){ //while there is a path between s and t with positive flow
        flow += fp.flow;
        unsigned int v = t;
        //cout << "Path..." << c+1 << endl;
        while(v != s){ //update the edge's in path with new flow
            //cout << "path...\n";
            
            Edge e = fp.path[v];
            Edge er = gr[e].reverse_edge;

           // printf("fp[v] = %lu  ", fp.path[v]);
           //cout << "e = " << e << "  er = " << er <<  endl;
           
//            
            gr[e].residual_capacity -= fp.flow;
            //cout << "Updated g[e]" << endl;
            gr[er].residual_capacity += fp.flow;
//            printf("%u -> %u [%u]\n",v, target(*e,g), g[*e].residual_capacity);

            c++;
            //exit(-1);
//           if(c == 3)
//            exit(-1);
           v = source(e, gr);
        }
                    
           c++;
        //get next path
        fp = dijkstra_flow(gr, s, t, k);   
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

