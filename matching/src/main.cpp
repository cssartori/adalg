/**
 * Implementation of Ford Fulkerson's algorithm as Fattest Path augmenting path.
 * Main function to solve the max-flow problem in stdin and return the value 
 * in stdout.
 * Carlo S. Sartori - 2017/1
 * CMP588 - Advanced Algorithms, UFRGS, Prof. Marcus Ritt
 */

#include <cstdio>
#include <chrono>
#include "../include/matgraph.h"

using namespace boost;
using namespace std;

//Read command line parameters
void read_parameters(int argc, char **argv, bool *time_info);
void usage(char **argv);

int main(int argc, char **argv){
	//time information
	bool time_info;

	read_parameters(argc, argv, &time_info);
	
	//graph dimensions, source and sink
	unsigned int n, m;
			
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;	

	//read graph from stdin	
	Graph g;
	read_dimacs_matching_graph(g, std::cin, &n, &m);
	
	if(time_info)		
   		start = std::chrono::system_clock::now();
   		
	//compute max-flow
    unsigned int mat_card = hopcroft_karp(g);
	    
	//print result
	//if(mflow != MAX_FLOW)
		printf("%u\n", mat_card);
	//else
		//printf("inf\n");
	
	if(time_info){
		end = std::chrono::system_clock::now();
		elapsed_seconds = end-start;	
		printf("Time: %.2f sec.\n", elapsed_seconds.count());
	}
	 		
	return 0;
}


//Read command line parameters
void read_parameters(int argc, char **argv, bool *time_info){

    //default values
	*time_info = false;
	
	if(argc > 1){
	    for(int i=1;i<argc;i++){
	        if(argv[i][0]=='-'){
	            switch(argv[i][1]){
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
	fprintf(stderr, "usage:\n%s [-t <print time information>]\n\t-time information: \ttoogle opton (default not toogled)\n", argv[0]);
}



