#ifndef __DGRAPH_H__
#define __DGRAPH_H__

/**
 * Code adapted from https://www.inf.ufrgs.br/~MRPRITT/doku.php?id=inf05016:2017-1-trabalhos
 * Implementation of Dijkstra's algorithm using k-heaps and hollow heaś.
 * Definition of data strutuctures for Graph representation and function call.
 * Carlo S. Sartori - 2017/1
 * CMP588 - Advanced Algorithms, UFRGS, Prof. Marcus Ritt
 */

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include "../../heap/include/heap.h"

//max value for distance
const unsigned int MAX_DIST = std::numeric_limits<unsigned int>::max(); 

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>::vertex_descriptor Node;
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>::edge_descriptor Edge;

//a vertex's data
struct VertexData{ };
 
//an edge's data
struct EdgeData{
  unsigned int weight; //weight is only positive for dijkstra
};
 
//A graph is an adjacency list represented by vectors (vecS)
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexData, EdgeData> Graph;


//Read a graph in DIMACS format from an input stream. 
//Note that Graph is not guaranteed to be assignable, thus the use of references
Graph& read_dimacs_graph(Graph& g, std::istream& in, unsigned int* n, unsigned int* m);

//Returns true if edge between node u and v exists
bool edge_exist(const Graph& g, unsigned int u, unsigned int v);

// Computes the shortest path between s-t in graph g using Dijkstra's algorithm implemented with heaps.
// Note that the heap h must be a min-heap in order to have valid functioning.
unsigned int dijkstra_heap(const Graph& g, unsigned int s, unsigned int t, Heap& h);

// Implementation of Dijkstra's algorithm with heaps for testing purposes (collects memory used, number of insertions, deletions, updates and execution time)
// Note that the heap h must be a min-heap in order to have valid functioning.
unsigned int dijkstra_heap_test(const Graph& g, unsigned int s, unsigned int t, Heap& h, unsigned int *n_ins, unsigned int *n_del, unsigned int *n_upd, long double *time, size_t *mem=NULL);

#endif //__DGRAPH_H__
