#include <cstdio>
#include <iostream>
#include <chrono>
#include "../include/chrisgraph.h"

using namespace std;
using namespace Christofides;

void read_parameters(int argc, char **argv, int *opmat, bool *time_info);
void usage(char **argv);

int main(int argc, char **argv){
    
    //matching algorithm option
    int opmat;
    //time information
	bool time_info;
	read_parameters(argc, argv, &opmat, &time_info);
    
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

    Distance d = run_christofides(g, opmat);
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
void read_parameters(int argc, char **argv, int *opmat, bool *time_info){

    //default values
	*opmat = BLOSSOM_MAT_ALG;
	*time_info = false;
	
	if(argc > 1){
	    for(int i=1;i<argc;i++){
	        if(argv[i][0]=='-'){
	            switch(argv[i][1]){
	                case 'm':
	                    i++;
	                    if(argv[i][0] == 'b')
	                        *opmat = BLOSSOM_MAT_ALG;
	                    else if(argv[i][0] == 'g')
	                        *opmat = GREEDY_MAT_ALG;
	                    else{
	                        fprintf(stderr, "Unkown matching algorithm %c \n", argv[i][0]);
	                        usage(argv);
	                        exit(-1);
	                    }    
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
	fprintf(stderr, "usage:\n%s [-m <matching algorithm>] [-t <print time information>]\n\t-matching algorithm: \tb for blossom V, g for greedy (default b)\n\t-time information: \ttoogle opton (default not toogled)\n", argv[0]);
}



