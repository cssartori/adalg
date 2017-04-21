#include <cstdio>
#include <chrono>
#include <math.h>
#include <vector>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include "../include/nheap.h"
#include "../include/dgraph.h"

static unsigned int NUM_EXP = 20;
static const int DEFAULT_HDIM = 2; //binary k-heap (2-heap)
static const char DEFAULT_HTYPE = 'h'; //hollow heaps


using namespace std;

vector<unsigned int> swaps;
vector<long double> times;
vector<unsigned int> e;

std::chrono::time_point<std::chrono::system_clock> tstart, tend;
std::chrono::duration<long double> elapsed_seconds;

void read_parameters(int argc, char **argv, char *op, char *htype, unsigned int *hd);
void usage(char **argv);


void test_delete(unsigned int hd){

	for(unsigned int i=1;i<=NUM_EXP;i++){
		unsigned int N = ((pow(hd,i)-1)/(hd-1));
		unsigned int n = 0;
		unsigned int k=0;
				
		NHeap h(hd, N*hd+1);
				
		while(n < N){
			h.insert(k, n);
            k++;
			n++;
		}

        unsigned int M = pow(hd, i-1); //number of nodes in last level
        n = 0;
        k = k + N + 1;
        
        while(n < M){
           	h.insert(k, n+N);
            k--;
			n++; 
        }
        
        
	   	tstart = std::chrono::system_clock::now();
	   	n=0;
		h.n_swaps = 0;
		while(n < M){
			n++;	
			h.deletemin();
		}
		
		tend = std::chrono::system_clock::now();
		elapsed_seconds = tend-tstart;	
		
		swaps[i] = h.n_swaps;
		e[i] = (i-1)*(pow(hd, i-1));
		times[i] = elapsed_seconds.count();
	}
	
	printf("%i,%i,%u,%u,%Le,%Le\n", 0, hd, swaps[0], e[0], times[0], (long double)0.0);
	printf("%i,%i,%u,%u,%Le,%Le\n", 1, hd, swaps[0], e[0], times[0], (long double)0.0);
	for(unsigned int j=2;j<swaps.size();j++){
	  printf("%i,%i,%u,%u,%Le,%Le\n", j, hd, swaps[j], e[j], times[j]-times[j-1], (times[j]-times[j-1])/e[j]);
	}	
}

void test_update(unsigned int hd){
	
	for(unsigned int i=1;i<=NUM_EXP;i++){
		unsigned int n = ((pow(hd,i)-1)/(hd-1));
		unsigned int k = ((pow(hd,i)-1)/(hd-1))*hd+1;
		unsigned int el = 0;
		
		NHeap h(hd, n*hd+1);
				
		for(unsigned int x=0;x<n;x++){
			h.insert(k, el++);
		}
		
		n = pow(hd, i);
		k = k+1;

		vector<unsigned int> els;
		for(unsigned int x=0;x<n;x++){
			h.insert(k, el);
			els.push_back(el);
			el++;
		}
		
		//start updating
		h.n_swaps = 0;
		k = n;

	   	tstart = std::chrono::system_clock::now();	
		
		for(unsigned int x=0;x<n;x++){
			h.update_key(els[x], k--);	
		}

	   	tend = std::chrono::system_clock::now();
		elapsed_seconds = tend-tstart;			
		
		swaps[i] = h.n_swaps;
		times[i] = elapsed_seconds.count();
		e[i] = (i)*pow(hd, i);
	}

	printf("%i,%i,%u,%u,%Le,%Le\n", 0, hd, swaps[0], e[0], times[0], (long double)0.0);	
	for(unsigned int j=1;j<swaps.size();j++){
		printf("%i,%i,%u,%u,%Le,%Le\n", j, hd, swaps[j], e[j], times[j]-times[j-1], (times[j]-times[j-1])/e[j]);
	}		
}


void test_insert(unsigned int hd){

	unsigned int n = ((pow(hd,NUM_EXP)-1)/(hd-1)); //limit
	unsigned int i=2;

	NHeap h(hd, n+1);
	h.insert(n, n);
	
	n--;
	unsigned int ninserts = 1;

   	tstart = std::chrono::system_clock::now();
   	unsigned int NI = ((pow(hd,i)-1)/(hd-1));
   	
	for(;n > 0 && i < NUM_EXP+1;n--){
		h.insert(n, n);
		ninserts++;
		if(NI == ninserts){
			swaps[i] = h.n_swaps;
		   	tend = std::chrono::system_clock::now();
			elapsed_seconds = tend-tstart;			
			times[i] = elapsed_seconds.count();
			e[i] = (i-1)*pow(hd,i-1);
			i++;
			NI = ((pow(hd,i)-1)/(hd-1));
			h.n_swaps = 0;
		}
	}
	
	printf("%i,%i,%u,%u,%Le,%Le\n", 0, hd, swaps[0], e[0], times[0], (long double)0.0);
	printf("%i,%i,%u,%u,%Le,%Le\n", 1, hd, swaps[1], e[1], times[1], (long double)0.0);	
	for(unsigned int j=2;j<swaps.size();j++){
		printf("%i,%i,%u,%u,%Le,%Le\n", j, hd, swaps[j], e[j], times[j]-times[j-1], (times[j]-times[j-1])/e[j]);
	}	
}


void test_scale(char htype, unsigned int hd, bool is_scale){
	
	unsigned int n,m;

	Graph g = read_dimacs(std::cin, &n, &m);
	if(n <= 1)
		return;	
	int ninf = 0;
	for(unsigned int i=0;i<NUM_EXP;i++){
		size_t mu = 0;
		unsigned int n_ins, n_del, n_upd;
		long double time;
		unsigned int d;

		do{
    		int s = rand()%n;
    		int t = rand()%n;
    		while(s == t)
    			t = rand()%n;

            if(htype == 'h')
    		    d = dijkstra_hheap_test(g, s, t, &n_ins, &n_del, &n_upd, &time, &mu);
    		else
      		    d = dijkstra_nheap_test(g, s, t, &n_ins, &n_del, &n_upd, &time, &mu, hd);
      		    
		}while(d == MAX_DIST && is_scale);	
		
		if(NUM_EXP != 1)
			printf("%u,", i);
				
		printf("%u,%u,%u,%u,%u,%lu,%Le,%u,%i\n", n, m, n_ins, n_del, n_upd, mu, time, d, hd);
		if(d == MAX_DIST)
			ninf++;
	}
	
	fprintf(stderr, "ninf = %i\n", ninf);
		
}

void test_validate(char htype, unsigned int hd){
	srand(time(0));
		
	unsigned int n,m;

	Graph g = read_dimacs(std::cin, &n, &m);
	if(n <= 1)
		return;	
	
	for(unsigned int i=0;i<NUM_EXP;i++){
		int s = rand()%n;
		int t = rand()%n;
		
		while(s == t || !edge_exist(g, s, t)){
			s = rand()%n;
			t = (t+1)%n;
		}
		unsigned int dst;
		if(htype == 'h')
		    dst = dijkstra_hheap(g, s, t);
		else
		    dst = dijkstra_nheap(g, s, t, hd);
		
		vector<unsigned int> dist(n);
  		vector<unsigned int> pred(n);
  		dijkstra_shortest_paths(g, s, weight_map(get(&EdgeData::weight,g)).distance_map(&dist[0]).predecessor_map(&pred[0]));
  		
  		int valid = 0;
  		if(dst != dist[t] && dst != MAX_DIST){
  			valid = -1;
  	    }

		printf("%u,%u,%u,%i,%i (%u -> %u)\n", i, dst, dist[t], valid, hd, s, t);
	}

	return;
}


int main(int argc, char **argv){
	srand(time(0));
	
	unsigned int hdim;
	char op;
	char htype;
	
	read_parameters(argc, argv, &op, &htype, &hdim);

	swaps = vector<unsigned int>(NUM_EXP+1, 0);
	times = vector<long double>(NUM_EXP+1, 0.0);
	e = vector<unsigned int>(NUM_EXP+1, 0);

	if(op == 'i')
		test_insert(hdim);
	else if(op == 'u')
		test_update(hdim);
	else if(op == 'd')
		test_delete(hdim);
	else if(op == 's')
		test_scale(htype, hdim, true);
	else if(op == 'c')
	    test_scale(htype, hdim, false);
	else if(op == 'v')
		test_validate(htype, hdim);
	
}

void read_parameters(int argc, char **argv, char *op, char *htype, unsigned int *hdim){
	if(argc < 3){
		usage(argv);
		exit(-1);
	}
	
	bool has_type = false;
	*hdim = DEFAULT_HDIM;
    *htype = DEFAULT_HTYPE;  
	
	for(int i=1;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 't':
					i++;
					*op = argv[i][0];
					if(*op != 'i' && *op != 'u' && *op != 'd' && *op != 's' && *op != 'c' && *op != 'v'){
    					fprintf(stderr, "Unkown test option %c \n", *op);
                		usage(argv);
                		exit(-1);
                    }
					has_type = true;
					break;
			    case 'h':
			        i++;
			        *htype = argv[i][0];
			        if(*htype != 'k' && *htype != 'h'){
	                    fprintf(stderr, "Unkown heap option %c\n", *htype);
	                    usage(argv);
	                    exit(-1);
	                }
			        break;
				case 'k':
					i++;
					*hdim = atoi(argv[i]);
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
	
	if(!has_type){
		usage(argv);
		exit(-1);
	}
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s -t <test type> [-h <heap type>] [-k <k-heap dimension>] [-n <number of tests>]\n\t-t test type: \t\ti, u, d, s, c, v\n\t-heap type: \t\t k for k-heap, h for hollow (default h)\n\t-k heap dimension: \tnatural numbers (default k=2)\n\t-n number of tests: \tnatural numbers (default n=20)\n", argv[0]);
}

