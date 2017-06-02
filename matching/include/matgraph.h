#ifndef __MATGRAPH_H__
#define __MATGRAPH_H__

/**
 * Code adapted from https://www.inf.ufrgs.br/~MRPRITT/doku.php?id=inf05016:2017-1-trabalhos
 * Implementation of Ford Fulkerson's algorithm as Fattest Path augmenting path.
 * Definition of data strutuctures for Graph representation and function call.
 * Carlo S. Sartori - 2017/1
 * CMP588 - Advanced Algorithms, UFRGS, Prof. Marcus Ritt
 */

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

// max value for fattest path
static const unsigned int MAX_FLOW = std::numeric_limits<unsigned int>::max(); 

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::undirectedS>::vertex_descriptor Node;
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::undirectedS>::edge_descriptor Edge;

//a vertex's data
struct VertexData{ };
 
//an edge's data
struct EdgeData{
    unsigned int id; //every edge has an unique ID
};
 
//A graph is an adjacency list represented by vectors (vecS)
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexData, EdgeData> Graph;

void read_dimacs_matching_graph(Graph& g, std::istream& in, unsigned int* n, unsigned int* m);

unsigned int hopcroft_karp(const Graph& g);

#endif //__MATGRAPH_H__
