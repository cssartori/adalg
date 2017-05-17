#ifndef __FFGRAPH_H__
#define __FFGRAPH_H__

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

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>::vertex_descriptor Node;
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>::edge_descriptor Edge;

//a vertex's data
struct VertexData{ };
 
//an edge's data
struct EdgeData{
    unsigned int capacity;            //capacity is only positive
    unsigned int residual_capacity; 
    Edge reverse_edge;                //backward edge for FF algorithm (O(1) access)
};
 
//A graph is an adjacency list represented by vectors (vecS)
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexData, EdgeData> Graph;


//Data to be collected when testing
struct TestData {
    unsigned int ndij; //number of calls to dijkstra
    unsigned int nins; //number of inserts in heap
    unsigned int ndel; //number of deletes in heap
    unsigned int nupd; //number of updates in heap
    unsigned int nswp; //number of swaps in the heap
    long double time; //time to execute the algorithm
    size_t mem; //amount of memory used
    unsigned int flow; //max flow returned by the algorithm
};

//Read a graph in DIMACS format from an input stream. 
//Note that Graph is not guaranteed to be assignable, thus the use of references
Graph& read_dimacs_max_flow(Graph &g, std::istream& in, unsigned int* n, unsigned int* m, unsigned int* s, unsigned int* t);

//Computes the max-flow between nodes s-t in graph g
unsigned int fattest_path(Graph& g, unsigned int s, unsigned int t, unsigned int k=2);

//Computes the max-flow between nodes s-t in graph g. Used for testing purposes. 
//(stores the number of calls to dijkstra algorithm, number of heap inserts, deletes and updates, as well as memmory consumption).
TestData fattest_path_test(Graph& g, unsigned int s, unsigned int t, unsigned int k=2);

#endif //__FFGRAPH_H__
