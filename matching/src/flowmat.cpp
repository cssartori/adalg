#include <iostream>
#include <cstring>
using namespace std;
 
#include <boost/graph/adjacency_list.hpp>
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
 
// Read a graph in DIMACS format from an input stream and return a Graph
void read_dimacs_flow_matching_graph(DiGraph& g, std::istream& in, unsigned int* n, unsigned int* m, unsigned int *s, unsigned int *t) {

	std::string line="", dummy;
	while (line[0] != 'p' || line[1] != ' ' || line[2] != 'e' || line[3] != 'd' || line[4] != 'g' || line[5] != 'e'){
        getline(in,line);
    }
 
  	//get nodes and edges
    sscanf(line.c_str(), "p edge %u %u\n", n, m);
	for(unsigned int x=0;x<*n+2;x++)
		add_vertex(g);
  	
  	*s = 0;
  	*t = *n+1;
  	  	
  	unsigned i=0;
  	while (i<*m) {
    	getline(in,line);
    	if (line[0] == 'e' && line[1] == ' ') {
      		unsigned int u,v;
      		sscanf(line.c_str(), "e %u %u\n", &u, &v);
        	
        	if(u > *n/2){
        	    unsigned int temp = u;
        	    u = v;
        	    v = temp;
        	}
        		
      		Edge e1, e2;
            bool in1, in2;
            tie(e1, in1) = add_edge(u, v, g);
            tie(e2, in2) = add_edge(v, u, g);
            
            g[e1].edge_capacity = 1;
            g[e2].edge_capacity = 0;
            g[e1].reverse_edge = e2;
            g[e2].reverse_edge = e1;
      		
      		i++;
    	}
  	}
  	
  	for(unsigned int i=1;i<=*n/2;i++){
  	    //connect source to all in v1
  	    Edge e1, e2; 
        bool in1, in2;   
  	    tie(e1, in1) = add_edge(*s, i, g);
        tie(e2, in2) = add_edge(i, *s, g);    
        g[e1].edge_capacity = 1;
        g[e2].edge_capacity = 0;
        g[e1].reverse_edge = e2;
        g[e2].reverse_edge = e1;
        
        //connect all v2 to target
        Edge e3, e4;    
  	    tie(e3, in1) = add_edge(i+(*n/2), *t, g);
        tie(e4, in2) = add_edge(*t, i+(*n/2), g);    
        g[e3].edge_capacity = 1;
        g[e4].edge_capacity = 0;
        g[e3].reverse_edge = e4;
        g[e4].reverse_edge = e3;
  	}

} 
 
 
 
 
int main(int argc, char *argv[]) {
      // (0) read graph
    DiGraph g;
    unsigned int n,m,s,t;
 
    read_dimacs_flow_matching_graph(g, cin, &n,&m,&s,&t);

    // (1) determine maximum flow
    unsigned int fat = push_relabel_max_flow(g, s, t,
                                            get(&EdgeInformation::edge_capacity,g),
                                            get(&EdgeInformation::edge_residual_capacity,g),
                                            get(&EdgeInformation::reverse_edge,g),
                                            get(boost::vertex_index, g));
    
    cout << fat << endl;
   
    return fat;
}
