#include <iostream>
#include <cassert>
using namespace std;
 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace boost;
 
// graph element descriptors
typedef adjacency_list_traits<vecS,vecS,undirectedS>::vertex_descriptor Node;
typedef adjacency_list_traits<vecS,vecS,undirectedS>::edge_descriptor Edge;
 
// information stored in vertices
struct VertexInformation {
  Node mate; // partner or graph_traits<Graph>::null_vertex()
};
// information stored in edges
struct EdgeInformation {};
 
// graph is an adjacency list represented by vectors
typedef adjacency_list<vecS,vecS,undirectedS,VertexInformation,EdgeInformation> Graph;

// Read a graph in DIMACS format from an input stream and return a Graph
void read_dimacs_matching_graph(Graph& g, std::istream& in, unsigned int* n, unsigned int* m) {
	std::string line="", dummy;
	while (line[0] != 'p' || line[1] != ' ' || line[2] != 'e' || line[3] != 'd' || line[4] != 'g' || line[5] != 'e'){
        getline(in,line);
    }
 
  	//get nodes and edges
    sscanf(line.c_str(), "p edge %u %u\n", n, m);
    
	for(unsigned int x=0;x<*n;x++)
		add_vertex(g);
  	  	
  	unsigned i=0;
  	while (i<*m) {
    	getline(in,line);
    	if (line[0] == 'e' && line[1] == ' ') {
      		unsigned int u,v;
      		sscanf(line.c_str(), "e %u %u\n", &u, &v);
      		add_edge(u-1,v-1,g);
      		
      		i++;
    	}
  	}
}
 
int main(int argc, char *argv[]) {  
  
    Graph g;
    unsigned int n, m;
    read_dimacs_matching_graph(g, cin, &n, &m);
  
    edmonds_maximum_cardinality_matching(g, get(&VertexInformation::mate,g));
    unsigned card = 0;
    graph_traits<Graph>::vertex_iterator vb, ve;
    for ( tie(vb, ve)=vertices(g); vb != ve; vb++)
        if (g[*vb].mate != graph_traits<Graph>::null_vertex())
            card++;
            
    cout << card/2 << endl;
    
    return 0;
}
