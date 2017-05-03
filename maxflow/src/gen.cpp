/**
 *   Generates random Graphs with given number of nodes/edges in DIMACS challenge format. 
 *   Adapted from: https://www.inf.ufrgs.br/~MRPRITT/doku.php?id=inf05016:2017-1-trabalhos
 */
 
#include <iostream>
#include "../include/dgraph.h"

using namespace std;
using namespace boost;
 
const unsigned maxweight = 10000;

void read_parameters(int argc, char **argv, unsigned int *n, double *p, bool *medges, int *ledges); 
void usage(char **argv); 
 
int main(int argc, char *argv[]) { 	  
	unsigned int n, m;
	double p;
	bool medges;
	int ledges;
	  
	read_parameters(argc, argv, &n, &p, &medges, &ledges);
	 
	Graph g;
	for(unsigned i=0; i<n; i++)
		add_vertex(g);
	
	srand48(time(0));
	srand(time(0));
	if(medges){
	    m = (unsigned int)(((n*log10(n))+n));
	    p =  pow(n, 0.1)*log10(n)/n;	
	    
	    if(ledges > 0){
	        m = ledges;
	    }
	    
	    //in case number of edges is bigger than the maximum
	    if(m >= (n*(n-1))){
		    p=1;
		    m = n*(n-1);
	    }
	    
	    
	    fprintf(stderr, "p = %f | n = %u | nlogn = %f | m = %u\n", p, n, log(n), m);
	    //edge created counter
		unsigned int mc = 0;
        
//        unsigned int s = rand()%n;
//        vector<bool> visited(n, false);
//        while(mc < m && mc < n-1){
//            visited[s] = true;
//            unsigned int t = rand()%n;
//            if(!visited[t]){
//                Edge e = add_edge(s,t,g).first;
//    		    g[e].weight = lrand48()%maxweight+0.01*maxweight;
//    		    mc ++;
//    		    s = t;
//    		    fprintf(stderr, "\rmc = %u", mc);
//		        fflush(stderr);
//            }            
//        }
        
		while(mc < m){
		    unsigned int s = rand()%n;
		    unsigned int t = rand()%n;
            
            if(s != t && !edge_exist(g, s, t)){
                Edge e = add_edge(s,t,g).first;
    		    g[e].weight = lrand48()%maxweight;//+0.01*maxweight;
//    		    Edge el = add_edge(t,s,g).first;
//    		    g[el].weight = lrand48()%maxweight;//+0.01*maxweight;
    		    mc ++;
    		    fprintf(stderr, "\rmc = %u", mc);
		        fflush(stderr);
            }
		
		
//			for(unsigned int i=0; i<n; i++){
//    		    for(unsigned int j=0; j<n; j++){
//      			    if (i != j && drand48() < p && !edge_exist(g, i, j)){
//      			        //fprintf(stderr, "Adding edge %u\n", mc);
//      			        mc++;
//        			    Edge e = add_edge(i,j,g).first;
//					    g[e].weight = lrand48()%maxweight;
//      			    }
//      			    if(mc >= m)
//      			        break;
//      		    }
//      		    if(mc >= m)
//      		        break;
//      		    fprintf(stderr, "\rmc = %u", mc);
//		        fflush(stderr);
//      	    }
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



void read_parameters(int argc, char **argv, unsigned int *n, double *p, bool *medges, int *ledges){
	if(argc < 4){
		usage(argv);
		exit(-1);
	}
	
	bool has_n = false;
	*medges = false;
	*ledges = -1;
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
					edge_p++;
					*medges = true;
					break;
			    case 'l':
			        edge_p++;
			        i++;
			        *ledges = atoi(argv[i]);
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
	} 
		
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s -n <number of nodes> [-m 'or' -p <probability of creating edge>]\n\t-n number of nodes: \t\tnatural numbers\n\t-m edge estimation: \t\tflag, no parameter needed\n\t-p prob. of creating edge: \treal numbers [0...1]\n", argv[0]);
}




