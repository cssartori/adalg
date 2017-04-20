#include <cstdio>
#include <chrono>
#include "../include/dgraph.h"
#include "../include/nheap.h"

using namespace boost;
using namespace std;


void usage(char **argv);
void read_parameters(int argc, char **argv, int *s, int *t, int *hd, bool *time_info);


int main(int argc, char **argv){
	//source and target nodes
	int s;
	int t;
	//heap dimension
	int hd;	
	//time information
	bool time_info;

	read_parameters(argc, argv, &s, &t, &hd, &time_info);
	
	//graph dimensions
	unsigned int n, m;
			
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;	

	//read graph from stdin	
	Graph g = read_dimacs(std::cin, &n, &m);
	
	if(time_info)		
   		start = std::chrono::system_clock::now();
   		
	//compute shortest path
	unsigned int dst = dijkstra_hheap(g, s, t, hd);		
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


void read_parameters(int argc, char **argv, int *s, int *t, int *hd, bool *time_info){
	if(argc < 3){
		usage(argv);
		exit(-1);
	}
	
	*s = atoi(argv[1]);
	*t = atoi(argv[2]);
	*hd = 2;
	*time_info = false;
	
	if(argc > 3)
		*hd = atoi(argv[3]);
	
	if(argc > 4){
		char op = argv[4][0];
		if(op == 't')
			*time_info = true;
		else{
			fprintf(stderr, "Unkown option %c.\n", op);
			usage(argv);
			exit(-1);
		}
	}
		
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s <source node> <target node> [<heap dimension>] [<time information>]\n\t-source node: \t\tnatural numbers\n\t-target node: \t\tnatural numbers\n\t-heap dimension: \tnatural numbers\n\t-time information: \toption t\n", argv[0]);
}



