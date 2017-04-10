/**
 *   Generates random Graphs with given number of nodes/edges in DIMACS challenge format. 
 *   Adapted from: https://www.inf.ufrgs.br/~MRPRITT/doku.php?id=inf05016:2017-1-trabalhos
 */
 
#include <iostream>
#include "../include/dgraph.h"

using namespace std;
using namespace boost;
 
const unsigned maxweight = 1000;

void read_parameters(int argc, char **argv, unsigned int *n, unsigned int *m, double *p, bool *medges); 
void usage(char **argv); 
 
int main(int argc, char *argv[]) { 	  
	unsigned int n, m;
	double p;
	bool medges;
	  
	read_parameters(argc, argv, &n, &m, &p, &medges);
	 
	Graph g;
	for(unsigned i=0; i<n; i++)
		add_vertex(g);
		
	//unsigned int mm = (unsigned int)(pow(n,1.001)*log(n));
	//m = max(m, mm);
	p =  pow(n, 0.1)*log(n)/n;	
	if(m >= (n*(n-1)/2)){
		p=1;
		m = n*(n-1)/2;
	}
	fprintf(stderr, "p = %f\n",p);
	srand48(time(0));
	srand(time(0));
	if(medges){
		unsigned int mc = 0;
        
		while(mc < m){
			for(unsigned int i=0; i<n; i++){
    		    for(unsigned int j=rand()%n; j<n; j++){
      			    if (i != j && drand48() < p && !edge_exist(g, i, j)){
      			        mc++;
        			    Edge e = add_edge(i,j,g).first;
					    g[e].weight = lrand48()%maxweight;
      			    }
      			    if(mc >= m)
      			        break;
      		    }
      	    }
		}

	}else{
		srand48(time(0));
		
		for(unsigned int i=0; i<n; i++){
    		for(unsigned int j=0; j<n; j++){
      			if (i != j && drand48() < p){
        			Edge e = add_edge(i,j,g).first;
					g[e].weight = lrand48()%maxweight;
      			}
      		}
      	}
	}
 	
 	
  	//print out in DIMACS challenge format
	printf("p sp %lu %lu\n", num_vertices(g), num_edges(g));
	for(unsigned int i=0;i<n;i++){
		graph_traits<Graph>::out_edge_iterator ie, fe;  //initial edge iterator and final edge
		for(tie(ie, fe) = out_edges(i, g); ie != fe; ie++)
	  		printf("a %u %lu %u\n", i+1, target(*ie, g)+1, g[*ie].weight);
  	}
  		
  	
}




void read_parameters(int argc, char **argv, unsigned int *n, unsigned int *m, double *p, bool *medges){
	if(argc < 5){
		usage(argv);
		exit(-1);
	}
	
	bool has_n = false;
	int edge_p = 0; //only one of the edge parameters should be informed
	
	
	for(int i=1;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'n':
					i++;
					*n = atoi(argv[i]);
					has_n = true;
					break;
				case 'm':
					i++;
					*m = atoi(argv[i]);
					edge_p++;
					*medges = true;
					break;
				case 'p':
					i++;
					*p = atof(argv[i]);
					edge_p++;
					*medges = false;
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
	
	if(!has_n || edge_p == 0){
		usage(argv);
		exit(-1);
	} else if(edge_p > 1){
		fprintf(stderr, "Either parameter -m or -p should be informed, but not both.\n");
		usage(argv);
		exit(-1);
	} /*else if(*medges && ((*n)*((*n)-1)) < (*m)){
		fprintf(stderr, "The number of edges exceeds the maximum for %u nodes (%u edges).\n", *n, ((*n)*((*n)-1)));
		usage(argv);
		exit(-1);
	}*/
		
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s -n <number of nodes> [-m <number of edges> 'or' -p <probability of creating edge>]\n\t-n number of nodes: \t\tnatural numbers\n\t-m number of edges: \t\tnatural numbers\n\t-p prob. of creating edge: \treal numbers [0...1]\n", argv[0]);
}




