/**
 *   Generates random Graphs with given number of nodes/edges in DIMACS challenge format. 
 *   Adapted from: https://www.inf.ufrgs.br/~MRPRITT/doku.php?id=inf05016:2017-1-trabalhos
 */
 
#include <iostream>
#include "../include/matgraph.h"

using namespace std;
using namespace boost;
 
void read_parameters(int argc, char **argv, unsigned int *n, double *p, bool *pmat, unsigned int *seed); 
void usage(char **argv); 
void print_flow(Graph& g);
void print_matching(Graph& g);

int main(int argc, char *argv[]) { 	  
	unsigned int seed = 0;
	unsigned int n, m;
	double p;
	bool pmat;	  

	read_parameters(argc, argv, &n, &p, &pmat, &seed);
	srand(seed);
	
    	m = p*n*log2(n);	 
	fprintf(stderr, "n = %u | p = %.2f | m = %u\n", n, p, m); 
	Graph g;
	for(unsigned i=0; i<2*n; i++)
		add_vertex(g);
	
 	unsigned int mc = 0; //edge counter
 	while(mc < m){
 	    unsigned int s = rand()%n;
 	    unsigned int t = rand()%n+n;
 	    bool added_edge = add_edge(s,t,g).second;
 	    if(added_edge)
 	        mc++;
 	}
 	
 	//print out in DIMACS challenge format
 	if(pmat)
		print_matching(g);
	else
		print_flow(g);

	fprintf(stderr, "Done.\n");
}

void print_matching(Graph& g){
	fprintf(stderr, "Printing graph in DIMACS matching\n");
  	printf("c Bi-partite graph for matching problem\n");
	printf("c Problem line (nodes, edges)\n");
    	printf("p edge %lu %lu\n", num_vertices(g), num_edges(g));
	printf("c Arc descriptor lines (u, v)\n");
	graph_traits<Graph>::edge_iterator ie, fe;
    	for ( tie(ie, fe)=edges(g); ie != fe; ie++){
		printf("e %lu %lu\n", source(*ie, g)+1, target(*ie, g)+1);
  	}
	printf("c\nc End of file");	
}


void print_flow(Graph& g){
	fprintf(stderr, "Printing graph in DIMACS max-flow\n");
	printf("c Max-flow version of a matching graph\n");
	printf("c Problem line (nodes, edges)\n");
	printf("p max %lu %lu\n", num_vertices(g)+2, num_edges(g)+num_vertices(g));
	printf("c source\n");
	unsigned int src = num_vertices(g)+1;
	printf("n %u s\n", src);
	printf("c target\n");
	unsigned int sink = num_vertices(g)+2;
	printf("n %u t\n", sink);
	printf("c Arc descriptor lines (from, to, capacity)\n");
	for(unsigned int i=0;i<num_vertices(g)/2;i++){
		printf("a %u %u 1\n", src, i+1);
	}	
	
	graph_traits<Graph>::edge_iterator ie, fe;
    	for ( tie(ie, fe)=edges(g); ie != fe; ie++){
		unsigned int s = source(*ie, g);
		unsigned int t = target(*ie, g);
		if(s > t){
			unsigned int temp = s;
			s = t;
			t = temp;
		}

		printf("a %u %u 1\n", s+1, t+1);
  	}	

	for(unsigned int i=num_vertices(g)/2;i<num_vertices(g);i++){
		printf("a %u %u 1\n", i+1, sink);
	}

	printf("c\nc End of file");		
}


void read_parameters(int argc, char **argv, unsigned int *n, double *p, bool *pmat, unsigned int *seed){
	if(argc < 5){
		usage(argv);
		exit(-1);
	}
	
	*seed = time(0);
	bool has_p = false;
	bool has_n = false;
	*pmat = true;	

	for(int i=1;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'n':
					i++;
					*n = atoi(argv[i]);
					has_n = true;
					break;
				case 'p':
					i++;
					*p = atof(argv[i]);
                    			has_p = true;
					break;
			    	case 's':
			        	i++;
			        	*seed = atoi(argv[i]);
			        	break;
				case 'f':
					*pmat = false;
					break;
				case 'b':
					*pmat = true;
					break;
				default:
					fprintf(stderr, "Parameter %c unkown.\n", argv[i][1]);
					usage(argv);
					exit(-1);
			}
		}else{
			fprintf(stderr, "Parameter %c unkown.\n", argv[i][1]);
			usage(argv);
			exit(-1);
		}
	}

    if(!has_n || !has_p){
        usage(argv);
        exit(-1);
    }
		
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s -n <number of nodes> -p <probability of creating edge> [-b print matching] [-f print max-flow] [-s <random seed>]\n\t-n number of nodes: \t\tnatural numbers\n\t-p prob. of creating edge: \treal numbers [0...1]\n\t-b print matching: \ttoggle option (default)\n\t-f print max-flow: \ttoggle option\n\t-s random seed: \tnatural numbers\n", argv[0]);
}




