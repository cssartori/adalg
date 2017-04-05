#ifndef __DGRAPH_H__
#define __DGRAPH_H__

/**
 * Code adapted from https://www.inf.ufrgs.br/~MRPRITT/doku.php?id=inf05016:2017-1-trabalhos
 * Implementation of Dijkstra's algorithm using n-heaps.
 * Definition of data strutuctures for Graph representation.
 * Carlo S. Sartori - UFRGS 2017/1
 */

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

const int MAX_DIST = 1e6; 

//a vertex's data
typedef struct {
  unsigned int v;
} VertexData;
 
//an edge's data
typedef struct  {
  unsigned int weight; //weight is only positive for dijkstra
} EdgeData;
 
 
//A graph is an adjacency list represented by vectors (vecS)
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexData, EdgeData> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Node;
typedef boost::graph_traits <Graph>::edge_descriptor Edge;

// Read a graph in DIMACS format from an input stream and return a Graph
Graph read_dimacs(std::istream& in, unsigned int* n, unsigned int* m);

// Computes the shortest path from node s to t in graph g using Dijkstra's algorithm and n-heaps
unsigned int dijkstra_nheap(const Graph& g, unsigned int s, unsigned int t, unsigned int nh=2);


#endif //__DGRAPH_H__
