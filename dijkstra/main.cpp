#include "dgraph.h"
#include "nheap.h"
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

//void test(Graph& g, unsigned int n, unsigned int nh=2){
//	srand(time(0));
//	
//	const unsigned int NT = n/2;
//	
//	unsigned int i = 0;
//	
//	while(i < NT){
//		int s = rand()%n;
//		int t = rand()%n;
//	
//		unsigned int dst = dijkstra_nheap(g, s, t, nh);
//		printf("%i %i -> %i: m = %lu ", i, s, t, dst);
//		
//		vector<unsigned> dist(n);
//  		vector<unsigned> pred(n);
//  		dijkstra_shortest_paths(g, s, weight_map(get(&EdgeData::weight,g)).distance_map(&dist[0]).predecessor_map(&pred[0]));
//  		
//	  	printf("| b = %lu\n", dist[t]);
//  		if(dst != dist[t])
//  			exit(-1);

//  		i++;	
//	}

//	return;
//}



int main(int argc, char **argv){
	
	if(argc < 3){
		printf("Usage: %s [source node] [target node]\n", argv[0]);
		return 0;
	}
	
	//source and target nodes
	int s = atoi(argv[1])-1;
	int t = atoi(argv[2])-1;
	//graph dimensions
	unsigned int n, m;
	
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;	

	//read graph from stdin	
	Graph g = read_dimacs(std::cin, &n, &m);
		
   	start = std::chrono::system_clock::now();
	//compute shortest path
	unsigned int dst = dijkstra_nheap(g, s, t);		
	//print result
	if(dst != MAX_DIST)
		cout << dst << endl;
	else
		cout << "inf" << endl;
	
	end = std::chrono::system_clock::now();
	elapsed_seconds = end-start;	
	printf("Time: %.2f sec.\n", elapsed_seconds.count());
	
//	
  	vector<unsigned> dist(n);
  	vector<unsigned> pred(n);
  	dijkstra_shortest_paths(g, s, weight_map(get(&EdgeData::weight,g)).distance_map(&dist[0]).predecessor_map(&pred[0]));
  	cerr << "Distance between " << s+1 << " and " << t+1 << " is " << dist[t] << endl;
	
 		
	return 0;
}
