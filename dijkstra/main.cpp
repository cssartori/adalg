#include "dgraph.h"
#include <cstdio>
#include <iostream>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <chrono>

using namespace boost;
using namespace std;

int main(int argc, char **argv){
	printf("%lu\n", sizeof(unsigned));

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
	printf("Graph read...\n");
	std::chrono::time_point<std::chrono::system_clock> start, end;
   	start = std::chrono::system_clock::now();
   	
	//compute shortest path
	int dst = dijkstra_nheap(g, s, t);		
	//print result
	printf("My result: %i\n", dst);	
	
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;	

	printf("Time: %.2f\n", elapsed_seconds.count());
	
  	vector<unsigned> dist(n);
  	vector<unsigned> pred(n);
  	dijkstra_shortest_paths(g, s, weight_map(get(&EdgeData::weight,g)).distance_map(&dist[0]).predecessor_map(&pred[0]));
  	cerr << "Distance between " << s << " and " << t << " is " << dist[t] << endl;
	
 		
	return 0;
}
