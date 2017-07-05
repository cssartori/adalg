#include <cstdio>
#include <chrono>
#include <math.h>
#include <fstream>
#include <map>
#include <vector>
#include "../include/chrisgraph.h"

using namespace std;
using namespace Christofides;

static unsigned int NUM_EXP = 10;
static const unsigned int DEFAULT_OPMAT = DEFAULT_MAT_ALG; //binary k-heap (2-heap)
Distance bksv;

void read_parameters(int argc, char **argv, unsigned int *opmat, double *p);
map<string,Distance> read_bks_file();
void usage(char **argv);


void test(int opmat, double p=0.0){

    std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;	
	
	ChrisGraph g;
	if(read_instance(g, std::cin) != 0){
        fprintf(stderr, "Error reading input file\n");
        exit(-1);
    }
	
	for(unsigned int n=0;n<NUM_EXP;n++){
    	start = std::chrono::system_clock::now();
	
	    Distance d = run_christofides(g, opmat, p);
	
	    end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        
        double dev = double(double(d-bksv)/bksv);
        
        bool cappr = true; //correct approximation
        if(dev > 0.5){
            cappr = false;
            if(opmat != GREEDY_MAT_ALG)
                fprintf(stderr, "Approximation is wrong : %f\n", dev);   
        }
        
        printf("%s,%u,%u,%u,%le,%u,%u,%.5f,%u,%.2f\n", g.name.c_str(), n, opmat, g.dim, elapsed_seconds.count(), d, bksv, dev, cappr,p);
    }
        	
}


int main(int argc, char **argv){
	unsigned int opmat; //matching algorithm option
	double p;
	read_parameters(argc, argv, &opmat, &p);
            
    test(opmat, p);
	
	return 0;
}

void read_parameters(int argc, char **argv, unsigned int *opmat, double *p){
    if(argc < 3){
        usage(argv);
        exit(-1);
    }
    
    bool has_bks = false;
	*opmat = DEFAULT_OPMAT;   	
	*p = 1.5;
	
	for(int i=1;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'b':
					i++;
					bksv = atoi(argv[i]);
					has_bks = true;    
					break;
			    case 'm':
	                    i++;
	                    if(string(argv[i]) == string("bc"))
	                        *opmat = BLOSSOM_COMPLETE_MAT_ALG;
	                    else if(string(argv[i]) == string("bs"))
	                        *opmat = BLOSSOM_SOLVE_MAT_ALG;
	                    else if(string(argv[i]) == string("g"))
	                        *opmat = GREEDY_MAT_ALG;
	                    else{
	                        fprintf(stderr, "Unkown matching algorithm %s \n", argv[i]);
	                        usage(argv);
	                        exit(-1);
	                    }    
	                    break;
	                case 'p':
	                    i++;
	                    if(*opmat != GREEDY_MAT_ALG){
	                        fprintf(stderr, "Greedy proportion should only be used with greedy matching algorithm.\n");
	                        usage(argv);
	                        exit(-1);
	                    }
	                    *p = atof(argv[i]);
	                    break;
				case 'n':
					i++;
					NUM_EXP = atoi(argv[i]);
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
	
	if(!has_bks){
	    fprintf(stderr, "A BKS value must be informed.\n");
	    usage(argv);
	    exit(-1);
	}
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s -b <bks value> [-m <matching algorithm>] [-n <number of tests>]\n\t-bks value: \t\tBKS value of the given instance for comparison\n\t-matching algorithm: \tbc for blossom V w/ complete graph, bs for efficient blossom V (buggy), g for greedy (default bc)\n\t-greedy proportion: \tproportion of edges calculated in greedy, real numbers (default p=1.5)\n\t-number of tests: \tnatural numbers (default n=10)\n", argv[0]);
}
