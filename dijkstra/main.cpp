#include "dgraph.h"
#include <cstdio>
#include <iostream>

using namespace boost;
using namespace std;

int main(int argc, char **argv){
	if(argc < 3){
		printf("Usage: %s [source node] [target node]\n", argv[0]);
		return 0;
	}
	
	//source and target nodes
	int s = atoi(argv[1]);
	int t = atoi(argv[2]);
	//graph dimensions
	unsigned int n, m;
	//read graph from stdin	
	Graph g = read_dimacs(std::cin, &n, &m);
	
	//compute shortest path
	int dst = dijkstra_nheap(g, s, t);		
	//print result
	printf("%i\n", dst);	
 		
	return 0;
}
