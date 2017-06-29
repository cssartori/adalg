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
static const unsigned int DEFAULT_OPMAT = BLOSSOM_MAT_ALG; //binary k-heap (2-heap)
static unsigned int seed; //random seed
//char* bfn = NULL; //BKS file name
Distance bksv;

void read_parameters(int argc, char **argv, unsigned int *opmat);
map<string,Distance> read_bks_file();
void usage(char **argv);


void test(int opmat){

    std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;	
	
	ChrisGraph g;
	if(read_instance(g, std::cin) != 0){
        fprintf(stderr, "Error reading input file\n");
        exit(-1);
    }
	
	for(unsigned int n=0;n<NUM_EXP;n++){
    	start = std::chrono::system_clock::now();
	
	    Distance d = run_christofides(g, opmat);
	
	    end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        
        double dev = double(double(d-bksv)/bksv);
        
        bool cappr = true; //correct approximation
        if(dev > 0.5){
            cappr = false;
            if(opmat != BLOSSOM_MAT_ALG)
                fprintf(stderr, "Approximation is wrong : %f\n", dev);   
        }
        
        printf("%s,%u,%u,%u,%le,%u,%u,%.5f,%u,%u\n", g.name.c_str(), n, opmat, g.dim, elapsed_seconds.count(), d, bksv, dev, cappr, seed);
    }
        	
}


int main(int argc, char **argv){
	unsigned int opmat; //matching algorithm option
	read_parameters(argc, argv, &opmat);
	srand(seed);
        
    test(opmat);
	
	return 0;
}

//map<string,Distance> read_bks_file(){
//    map<string,Distance> BKS;

//	ifstream bfile (bfn);
//    if(bfile.is_open()){
//        string line;
//        while(getline (bfile,line)){
//            if(line[0] == '#')
//                continue;
//            string iname="", ivalue="";
//            unsigned int i;
//            for(i=0;i<line.size();i++)
//                if(line[i] == ',') break;
//                else iname += line[i];
//           
//            for(i+=1;i<line.size();i++)
//                ivalue += line[i];
//           
//            Distance value = atoi(ivalue.c_str());
//            
//            BKS[iname] = value;             
//        }
//        bfile.close();
//    }else{
//	    fprintf(stderr, "Could not open BKS file %s\n", bfn);
//	    exit(-1);
//	}
//	
//	return BKS;
//} 

void read_parameters(int argc, char **argv, unsigned int *opmat){
    if(argc < 3){
        usage(argv);
        exit(-1);
    }
    
    bool has_bks = false;
	seed = time(0);
	*opmat = DEFAULT_OPMAT;   	
	
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
	
	if(!has_bks){
	    fprintf(stderr, "A BKS value must be informed.\n");
	    usage(argv);
	    exit(-1);
	}
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s -b <bks value> [-m <matching algorithm>] [-n <number of tests>] [-s <random seed>]\n\t-bks value: \tBKS value of the given instance for comparison\n\t-matching algorithm: \tb for blossom V, g for greedy (default b)\n\t-number of tests: \tnatural numbers (default n=10)\n\t-random seed: \t\tseed to be used by generator (default s=time(0))\n", argv[0]);
}
