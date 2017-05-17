#include <cstdio>
#include <chrono>
#include <math.h>
#include <vector>
#include "../include/ffgraph.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
//#include "boost/graph/copy.hpp"

static unsigned int NUM_EXP = 20;
static const int DEFAULT_HDIM = 2; //binary k-heap (2-heap)
static unsigned int seed; //random seed

using namespace std;
using namespace boost;


void read_parameters(int argc, char **argv, unsigned int *k);
void usage(char **argv);

//method to copy a graph since boost does not copy the edge references for FF algorithm
Graph& copy_graph(Graph& src, Graph& dest){
    //add vertices to graph g
	for(unsigned int x=0;x<num_vertices(src);x++)
		add_vertex(dest);
  	
  	
  	graph_traits<Graph>::edge_iterator ie, fe;  //initial edge iterator and final edge
	for(tie(ie, fe) = edges(src); ie != fe; ie++){
	    //forward edge	
        pair<Edge, bool> fep = edge(source(*ie,src),target(*ie,src),dest);
        if(fep.second){ //edge already exists as reverse edge
            dest[fep.first].capacity = src[*ie].capacity;
            dest[fep.first].residual_capacity += src[*ie].capacity;
        }else{ //create new edge    	
            fep.first = add_edge(source(*ie,src),target(*ie,src),dest).first;
	    	dest[fep.first].capacity = src[*ie].capacity;
	    	dest[fep.first].residual_capacity = src[*ie].capacity;
		}
			
		//reverse edge
        pair<Edge, bool> rep = edge(target(*ie,src),source(*ie,src),dest);
        if(!rep.second){ //create new edge
    	    rep.first = add_edge(target(*ie,src),source(*ie,src),dest).first;
	    	dest[rep.first].residual_capacity = 0;
	    }

		dest[fep.first].reverse_edge = rep.first;		
		dest[rep.first].reverse_edge = fep.first;
	}
  	
  	return dest;
}

void test_scale(unsigned int k=2){
	unsigned int n,m; //number of vertices and edges in graph g
	unsigned int s,t; //source and sink of flow
    
    Graph g;
	g = read_dimacs_max_flow(g, std::cin, &n, &m, &s, &t);
	
	if(n <= 1)
		return;	
		
	int ninf = 0;   
	for(unsigned int i=0;i<NUM_EXP;i++){
        Graph gl;
        copy_graph(g, gl);
        TestData td;
		do{           
            td = fattest_path_test(gl, s, t, k);   
		}while(td.flow == MAX_FLOW);					
		
		printf("%i,%i,%u,%u,%u,%u,%u,%u,%u,%lu,%Le,%u,%u\n", i, k, n, m, td.ndij, td.nins, td.ndel, td.nupd, td.nswp, td.mem, td.time, td.flow, seed);
		if(td.flow == MAX_FLOW)
			ninf++;
	}
	
	fprintf(stderr, "ninf = %i\n", ninf);
}


int main(int argc, char **argv){
	unsigned int k; //heap dimension
	read_parameters(argc, argv, &k);
	srand(seed);
    
    test_scale(k);
	
	return 0;
}

void read_parameters(int argc, char **argv, unsigned int *k){
	seed = time(0);
	*k = DEFAULT_HDIM;
	
	for(int i=1;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'k':
					i++;
					*k = atoi(argv[i]);
					break;
				case 'n':
					i++;
					NUM_EXP = atoi(argv[i]);
					break;
			    case 's':
			        i++;
			        seed = atoi(argv[i]);
			        break;
				default:
					fprintf(stderr, "Unkown parameter %s \n", argv[i]);
					usage(argv);
					exit(-1);
			}
		}else{
			fprintf(stderr, "Unkown parameter %s \n", argv[i]);
			usage(argv);
			exit(-1);
		}
	}
	
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s [-k <k-heap dimension>] [-n <number of tests>] [-s <random seed>]\n\t-k heap dimension: \tnatural numbers (default k=2)\n\t-n number of tests: \tnatural numbers (default n=20)\n\t-s random seed: \tseed to be used by generator (default s=time(0))\n", argv[0]);
}

