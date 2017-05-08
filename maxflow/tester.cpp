/**
 * \file maxflow.cpp
 *   \author Marcus Ritt <mrpritt@inf.ufrgs.br> 
 *   \version $Id: emacs 2872 2009-01-31 01:46:50Z ritt $
 *   \date Time-stamp: <2015-09-22 21:17:31 ritt>
 *
 * Read a maximum flow problem in DIMACS format and output the maximum flow.
 *
 */
#include <iostream>
#include <cstring>
using namespace std;
 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace boost;
 
// graph element descriptors
typedef adjacency_list_traits<vecS,vecS,directedS>::vertex_descriptor DiNode;
typedef adjacency_list_traits<vecS,vecS,directedS>::edge_descriptor Edge;
 
// a directed graph with reverse edges
struct VertexInformation {};
typedef unsigned Capacity;
struct EdgeInformation {
  Capacity edge_capacity;
  Capacity edge_residual_capacity;
  Edge reverse_edge;
};
 
typedef adjacency_list<vecS,vecS,directedS,VertexInformation,EdgeInformation> DiGraph;
 
int main(int argc, char *argv[]) {
  // (0) read graph
 
  DiGraph g;
  DiNode s,t;
     
  read_dimacs_max_flow(g,
                       get(&EdgeInformation::edge_capacity,g),
                       get(&EdgeInformation::reverse_edge,g),
                       s, t);
 
  // (1) determine maximum flow
  unsigned int fat = push_relabel_max_flow(g, s, t,
                                get(&EdgeInformation::edge_capacity,g),
                                get(&EdgeInformation::edge_residual_capacity,g),
                                get(&EdgeInformation::reverse_edge,g),
                                get(boost::vertex_index, g));
  cout << fat << endl;
                                
//  Graph gr;
//  Node sr,tr;
//  unsigned n;
//  unsigned m;
//  unsigned s;
//  unsigned t;
//    printf("Reading instance file...\n");
//    gr = read_dimacs_max_flow(std::cin, &n,&m,&s,&t);
//    printf("Running dijkstra %u -> %u...\n", s, t);
//    unsigned int fat = fattest_path(gr, s, t);
//     cout << "fat = " << fat << endl;
//  read_dimacs_max_flow(gr,
//                       get(&EdgeData::capacity,gr),
//                       get(&EdgeData::reverse_edge,gr),
//                       sr, tr);
// 
//   (1) determine maximum flow
//  cout << push_relabel_max_flow(gr, sr, tr,
//                                get(&EdgeData::capacity,gr),
//                                get(&EdgeData::residual_capacity,gr),
//                                get(&EdgeData::reverse_edge,gr),
//                                get(boost::vertex_index, gr)) << endl;    
    
    return fat;
}
