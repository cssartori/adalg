#include <cstdio>
#include <chrono>
#include <math.h>
#include <vector>
#include "../include/ffgraph.h"


static unsigned int NUM_EXP = 20;
static const int DEFAULT_HDIM = 2; //binary k-heap (2-heap)
static unsigned int seed; //random seed

using namespace std;

void read_parameters(int argc, char **argv, unsigned int *k);
void usage(char **argv);


void test_scale(unsigned int k=2){
	unsigned int n,m; //number of vertices and edges in graph g
	unsigned int s,t; //source and sink of flow
    
    Graph g;
	g = read_dimacs_max_flow(g, std::cin, &n, &m, &s, &t);
	
	if(n <= 1)
		return;	
		
	int ninf = 0;   
	for(unsigned int i=0;i<NUM_EXP;i++){
		size_t mu = 0;
		unsigned int ndij, nins, ndel, nupd;
		long double time;
		unsigned int d;

		do{           
            d = fattest_path_test(g, s, t, &ndij, &nins, &ndel, &nupd, &time, &mu, k);    
		}while(d == MAX_FLOW);					
		
		printf("%i,%i,%u,%u,%u,%u,%u,%u,%lu,%Le,%u,%u\n", i, k, n, m, ndij, nins, ndel, nupd, mu, time, d, seed);
		
		if(d == MAX_FLOW)
			ninf++;
	}
	
	fprintf(stderr, "ninf = %i\n", ninf);
}


int main(int argc, char **argv){
	unsigned int k; //heap dimension
	read_parameters(argc, argv, &k);
	srand(seed);
    
    test_scale(k);
	
	return 0;
}

void read_parameters(int argc, char **argv, unsigned int *k){
	seed = time(0);
	*k = DEFAULT_HDIM;
	
	for(int i=1;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'k':
					i++;
					*k = atoi(argv[i]);
					break;
				case 'n':
					i++;
					NUM_EXP = atoi(argv[i]);
					break;
			    case 's':
			        i++;
			        seed = atoi(argv[i]);
			        break;
				default:
					fprintf(stderr, "Unkown parameter %s \n", argv[i]);
					usage(argv);
					exit(-1);
			}
		}else{
			fprintf(stderr, "Unkown parameter %s \n", argv[i]);
			usage(argv);
			exit(-1);
		}
	}
	
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s [-k <k-heap dimension>] [-n <number of tests>] [-s <random seed>]\n\t-k heap dimension: \tnatural numbers (default k=2)\n\t-n number of tests: \tnatural numbers (default n=20)\n\t-s random seed: \tseed to be used by generator (default s=time(0))\n", argv[0]);
}

