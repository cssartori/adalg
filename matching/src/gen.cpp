/**
 *   Generates random Graphs with given number of nodes/edges in DIMACS challenge format. 
 *   Adapted from: https://www.inf.ufrgs.br/~MRPRITT/doku.php?id=inf05016:2017-1-trabalhos
 */
 
#include <iostream>
#include "../include/matgraph.h"

using namespace std;
using namespace boost;
 
const unsigned maxweight = 10000;

void read_parameters(int argc, char **argv, unsigned int *n, double *p, unsigned int *seed); 
void usage(char **argv); 
 
int main(int argc, char *argv[]) { 	  
    unsigned int seed = 0;
	unsigned int n, m;
	double p;
	  
	read_parameters(argc, argv, &n, &p, &seed);
    srand(seed);
	
	m = ceil(n*(n*p));
	 
	fprintf(stderr, "n = %u | p = %.2f | m = %u\n", n, p, m); 
	Graph g;
	for(unsigned i=0; i<2*n; i++)
		add_vertex(g);
	
//	for(unsigned i=0; i<n; i++){
//        for(unsigned j=n; j<2*n; j++){
//            double r = drand48();
//            //fprintf(stderr, "r = %.2f\n", r);
//            if (r < p) {
//                Edge e = add_edge(i,j,g).first;
//                //fprintf(stderr, "Edge size %u\n", sizeof(Edge));
//            }
//        }
//    }
 	unsigned int mc = 0; //edge counter
 	while(mc < m){
 	    unsigned int s = rand()%n;
 	    unsigned int t = rand()%n+n;
 	    bool added_edge = add_edge(s,t,g).second;
 	    if(added_edge)
 	        mc++;
 	}
 	
 	fprintf(stderr, "Printing graph\n");
  	//print out in DIMACS challenge format
  	printf("c Bi-partite graph\n\n");
    printf("p edge %lu %lu\n", num_vertices(g), num_edges(g));
	graph_traits<Graph>::edge_iterator ie, fe;
    for ( tie(ie, fe)=edges(g); ie != fe; ie++){
	  		printf("e %lu %lu\n", source(*ie, g)+1, target(*ie, g)+1);
  	}	
}



void read_parameters(int argc, char **argv, unsigned int *n, double *p, unsigned int *seed){
	if(argc < 5){
		usage(argv);
		exit(-1);
	}
	
	*seed = time(0);
	bool has_n = false;
	bool has_p = false;
	
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
	fprintf(stderr, "usage:\n%s -n <number of nodes> -p <probability of creating edge> [-s <random seed>]\n\t-n number of nodes: \t\tnatural numbers\n\t-p prob. of creating edge: \treal numbers [0...1]\n\t-s random seed: \tnatural numbers\n", argv[0]);
}




