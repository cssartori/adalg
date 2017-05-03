#include <cstdio>
#include <chrono>
#include "../include/dgraph.h"
#include "../include/nheap.h"

using namespace boost;
using namespace std;

static const char DEFAULT_HTYPE = 'h'; //hollow heaps
static const int DEFAULT_HDIM = 2; //binary k-heap (2-heap)

void usage(char **argv);
void read_parameters(int argc, char **argv, int *s, int *t, char *htype, int *hdim, bool *time_info);


int main(int argc, char **argv){
	//source and target nodes
	int s;
	int t;
	//heap type (k-heap or hollow heap)
	char htype;
	//heap dimension
	int hd;	
	//time information
	bool time_info;

	read_parameters(argc, argv, &s, &t, &htype, &hd, &time_info);
	
	//graph dimensions
	unsigned int n, m;
			
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;	

	//read graph from stdin	
	Graph g = read_dimacs(std::cin, &n, &m);
	
	if(time_info)		
   		start = std::chrono::system_clock::now();
   		
	//compute shortest path
	unsigned int dst;
	if(htype == 'h')
	    dst = dijkstra_hheap(g, s, t);		
	else
	    dst = dijkstra_nheap(g, s, t, hd);
	    
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


void read_parameters(int argc, char **argv, int *s, int *t, char *htype, int *hdim, bool *time_info){
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



