/**
 * \file gen.cpp
 *   \author Marcus Ritt <mrpritt@inf.ufrgs.br> 
 *   \version $Id: emacs 2872 2009-01-31 01:46:50Z ritt $
 *   \date Time-stamp: <2011-08-24 15:17:49 ritt>
 */
 
#include <iostream>
#include <cassert>
using namespace std;
 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace boost;
 
// information stored in vertices
struct VertexInformation {
  unsigned component;
};
 
// information stored in edges
struct EdgeInformation {
  unsigned weight;
};
 
const unsigned maxweight = 1000;
 
// graph is an adjacency list represented by vectors
typedef adjacency_list<vecS, vecS, directedS,VertexInformation,EdgeInformation> Graph;
typedef graph_traits<Graph>::vertex_descriptor Node;
typedef graph_traits <Graph>::edge_descriptor Edge;
 
int main(int argc, char *argv[]) {
  assert(argc == 3);
  unsigned n = atoi(argv[1]);
  double p = atof(argv[2]);
 
  srand48(time(0));
 
  // (1) generate random graph
  Graph g;
 
  for(unsigned i=0; i<n; i++)
    add_vertex(g);
 
  for(unsigned i=0; i<n; i++)
    for(unsigned j=0; j<n; j++)
      if (i != j && drand48() < p) {
        Edge e = add_edge(i,j,g).first;
	g[e].weight = lrand48()%maxweight;
      }
 
 
 	//cout << "Num edges = " << num_edges(g) << "\n";
 	
 
  // (2) print example path
  unsigned src = lrand48()%num_vertices(g);
  unsigned dst = lrand48()%num_vertices(g);
 
  vector<unsigned> dist(n);
  vector<unsigned> pred(n);
  dijkstra_shortest_paths(g,src,weight_map(get(&EdgeInformation::weight,g)).distance_map(&dist[0]).predecessor_map(&pred[0]));
  cerr << "Distance between " << src+1 << " and " << dst+1 << " is " << dist[dst] << endl;
 
  // (3) print out in DIMACS challenge format
  cout << "p sp " << num_vertices(g) << " " << num_edges(g) << endl;
  graph_traits<Graph>::edge_iterator eb, ee;
  for ( tie(eb, ee)=edges(g); eb != ee; eb++)
    cout << "a " << source(*eb,g)+1 << " " << target(*eb, g)+1 << " " << g[*eb].weight << endl;
}


