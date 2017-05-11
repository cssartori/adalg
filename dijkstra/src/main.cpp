/**
 * Implementation of Dijkstra's algorithm using heaps.
 * It can use two types of heaps: k-heaps and hollow heaps.
 * Main function to solve the shortest path problem in stdin and return the 
 * value in stdout.
 * Carlo S. Sartori - 2017/1
 * CMP588 - Advanced Algorithms, UFRGS, Prof. Marcus Ritt
 */

#include <cstdio>
#include <chrono>
#include "../include/dgraph.h"
#include "../../heap/include/nheap.h"
#include "../../heap/include/hheap.h"

using namespace boost;
using namespace std;

static const char DEFAULT_HTYPE = 'k'; //hollow heaps
static const int DEFAULT_HDIM = 2; //binary k-heap (2-heap)

//Read command line parameters
void read_parameters(int argc, char **argv, unsigned int *s, unsigned int *t, char *htype, unsigned int *hdim, bool *time_info);
void usage(char **argv);

int main(int argc, char **argv){
	//source and target nodes
	unsigned int s, t;
	//heap type (k-heap or hollow heap)
	char htype;
	//heap dimension
	unsigned int hdim;	
	//time information
	bool time_info;

	read_parameters(argc, argv, &s, &t, &htype, &hdim, &time_info);
	
	//graph dimensions
	unsigned int n, m;
			
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;	

	//read graph from stdin
	Graph g;	
	g = read_dimacs_graph(g, std::cin, &n, &m);
	
	if(time_info)		
   		start = std::chrono::system_clock::now();
   	
   	Heap *h;
   	if(htype == 'k')
   	    h = new NHeap(num_vertices(g), hdim);
   	else
   	    h = new HHeap(num_vertices(g));
   	    	
	//compute shortest path
	unsigned int dst = dijkstra_heap(g, s, t, *h);
	    
	//print result
	if(dst != MAX_DIST)
		printf("%u\n", dst);
	else
		printf("inf\n");
	
	if(time_info){
		end = std::chrono::system_clock::now();
		elapsed_seconds = end-start;	
		printf("Time: %.2f sec.\n", elapsed_seconds.count());
	}
	 		
	return 0;
}

//Read command line parameters
void read_parameters(int argc, char **argv, unsigned int *s, unsigned int *t, char *htype, unsigned int *hdim, bool *time_info){
	if(argc < 3){
		usage(argv);
		exit(-1);
	}
	
	*s = atoi(argv[1]);
	*t = atoi(argv[2]);
	*hdim = DEFAULT_HDIM;
	*htype = DEFAULT_HTYPE;
	*time_info = false;
	
	if(argc > 3){
	    for(int i=3;i<argc;i++){
	        if(argv[i][0]=='-'){
	            switch(argv[i][1]){
	                case 'h':
	                    i++;
	                    *htype = argv[i][0];
	                    if(*htype != 'k' && *htype != 'h'){
	                        fprintf(stderr, "Unkown heap option %c\n", *htype);
	                        usage(argv);
	                        exit(-1);
	                    }
	                    break;
	                case 'k':
	                    i++;
	                    *hdim = atoi(argv[i]);
	                    break;
	                case 't':
	                    *time_info = true;
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
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s <source node> <target node> [-h <heap type>][-k <k-heap dimension>] [-t <print time information>]\n\t-source node: \t\tnatural numbers\n\t-target node: \t\tnatural numbers\n\t-heap type: \t\tk for k-heaps, h for hollow heaps (default h)\n\t-k-heap dimension: \tnatural numbers (default k=2)\n\t-time information: \ttoogle opton (default not toogled)\n", argv[0]);
}



