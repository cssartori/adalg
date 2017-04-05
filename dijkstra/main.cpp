#include "dgraph.h"
#include "nheap.hpp"
#include <cstdio>
#include <iostream>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/functional/hash.hpp>
#include <chrono>
#include <unordered_map>
#include <map>
#include <vector>

using namespace boost;
using namespace std;


bool comp(int a, int b){
	return a<b;
}

int main(int argc, char **argv){
	
//	unsigned int n = pow(2, 25) - 1;
//	NHeap<int>  h(2, n);
//	
//	
//	for(int i=0;i<200;i++){
//		h.insert(200-i);
//	}
//	
//	h.update_key(100, 500);
//	
//	for(int i=0;i<200;i++){
//		printf("%i\n", h.getmin());
//		h.deletemin();
//	}
//		
//	int k;
//	cin >> k;

	if(argc < 3){
		printf("Usage: %s [source node] [target node]\n", argv[0]);
		return 0;
	}
	
	//source and target nodes
	int s = atoi(argv[1])-1;
	int t = atoi(argv[2])-1;
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
  	cerr << "Distance between " << s+1 << " and " << t+1 << " is " << dist[t] << endl;
	
 		
	return 0;
}
