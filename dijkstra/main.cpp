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


void test(Graph& g, unsigned int n, unsigned int nh=2){
	srand(time(0));
	
	const unsigned int NT = n/2;
	
	unsigned int i = 0;
	
	while(i < NT){
		int s = rand()%n;
		int t = rand()%n;
	
		unsigned int dst = dijkstra_nheap(g, s, t, nh);
		printf("%i %i -> %i: m = %lu ", i, s, t, dst);
		
		vector<unsigned> dist(n);
  		vector<unsigned> pred(n);
  		dijkstra_shortest_paths(g, s, weight_map(get(&EdgeData::weight,g)).distance_map(&dist[0]).predecessor_map(&pred[0]));
  		
	  	printf("| b = %lu\n", dist[t]);
  		if(dst != dist[t])
  			exit(-1);

  		i++;	
	}

	return;
}



int main(int argc, char **argv){
	
//	unsigned int n1 = pow(2, 25) - 1;
//	NHeap h(2, n1);
//	
//	
//	for(int i=0;i<200;i++){
//		h.insert(200-i, 200-i);
//	}
//	
//	h.update_key(100, 500);
//	h.update_key(101, 499);
//	
//	for(int i=0;i<200;i++){
//		printf("%i, %i\n", h.getminKey(), h.getmin());
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
	
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;	
   	start = std::chrono::system_clock::now();	
	
	//read graph from stdin	
	Graph g = read_dimacs(std::cin, &n, &m);
	
	//test(g, n); 	return 0;
	
	end = std::chrono::system_clock::now();
	elapsed_seconds = end-start;
	printf("Graph read in %.2f sec.\n", elapsed_seconds.count());
	
   	start = std::chrono::system_clock::now();
   	
	//compute shortest path
	unsigned int dst = dijkstra_nheap(g, s, t);		
	//print result
	printf("My result: %lu\n", dst);	
	
	end = std::chrono::system_clock::now();
	elapsed_seconds = end-start;	

	printf("Time: %.2f sec.\n", elapsed_seconds.count());
	
  	vector<unsigned> dist(n);
  	vector<unsigned> pred(n);
  	dijkstra_shortest_paths(g, s, weight_map(get(&EdgeData::weight,g)).distance_map(&dist[0]).predecessor_map(&pred[0]));
  	cerr << "Distance between " << s+1 << " and " << t+1 << " is " << dist[t] << endl;
	
 		
	return 0;
}
