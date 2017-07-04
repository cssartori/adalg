#include <cstdio>
#include <iostream>
#include <chrono>
#include "../include/chrisgraph.h"

using namespace std;
using namespace Christofides;

void read_parameters(int argc, char **argv, int *opmat, double *p, bool *time_info);
void usage(char **argv);

int main(int argc, char **argv){
    
    //matching algorithm option
    int opmat;
    //greedy cache proportion
    double p;
    //time information
	bool time_info;
	read_parameters(argc, argv, &opmat, &p, &time_info);
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;	
	
    ChrisGraph g;
    if(read_instance(g, std::cin) != 0){
        cout << "Error reading input file\n";
        return -1;
    }
    //cout << "Read input file...\n";
    
    if(time_info)		
   		start = std::chrono::system_clock::now();

    Distance d = run_christofides(g, opmat, p);
    cout << d << endl;
        
    if(time_info){
		end = std::chrono::system_clock::now();
		elapsed_seconds = end-start;	
		printf("Time: %.2f sec.\n", elapsed_seconds.count());
	}
    
    //cout << "Christofides algorithm finished with " << d << endl;
    
    return 0;
}

//Read command line parameters
void read_parameters(int argc, char **argv, int *opmat, double *p, bool *time_info){

    //default values
	*opmat = BLOSSOM_COMPLETE_MAT_ALG;
	*time_info = false;
	*p = 1.5;
	
	if(argc > 1){
	    for(int i=1;i<argc;i++){
	        if(argv[i][0]=='-'){
	            switch(argv[i][1]){
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
	                case 't':
	                    *time_info = true;
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
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s [-m <matching algorithm>] [-p <greedy proportion>] [-t <print time information>]\n\t-matching algorithm: \tbc for blossom V w/ complete graph, bs for efficient blossom V (buggy), g for greedy (default bc)\n\t-greedy proportion: \tproportion of edges calculated in greedy, real numbers (default p=1.5)\n\t-time information: \ttoogle opton (default not toogled)\n", argv[0]);
}



