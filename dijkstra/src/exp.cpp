#include <cstdio>
#include <chrono>
#include <math.h>
#include <vector>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include "../include/nheap.h"
#include "../include/dgraph.h"

unsigned int NUM_EXP = 20;

using namespace std;

vector<unsigned int> swaps;
vector<long double> times;
vector<unsigned int> e;

std::chrono::time_point<std::chrono::system_clock> tstart, tend;
std::chrono::duration<long double> elapsed_seconds;

void read_parameters(int argc, char **argv, char *op, unsigned int *hd);
void usage(char **argv);

void test_delete(unsigned int hd){
	NHeap h(hd, pow(hd, NUM_EXP)+1);
	
	for(unsigned int i=1;i<=NUM_EXP;i++){
		int N = ((pow(hd,i)-1)/(hd-1));
		int n = N;
		int k=0;
		while(n > 0){
			n--;
			h.insert(rand()%N, n);
		}
        
        n=0;
        N = pow(hd, i-1);
	   	tstart = std::chrono::system_clock::now();
		h.n_swaps = 0;
		while(n < N){
			n++;	
			h.deletemin();
		}
		
		tend = std::chrono::system_clock::now();
		elapsed_seconds = tend-tstart;	
		
		swaps[i] = h.n_swaps;
		e[i] = i*pow(hd,i);
		times[i] = elapsed_seconds.count();
	}
	
	printf("%i %u %u %Le %Le\n", 0, swaps[0], e[0], times[0], (long double)0.0);
	for(unsigned int j=1;j<swaps.size();j++){
		printf("%i %u %u %Le %Le\n", j, swaps[j], e[j], times[j]-times[j-1], (times[j]-times[j-1])/e[j]);
	}	
}

void test_update(unsigned int hd){
	
	for(unsigned int i=1;i<=NUM_EXP;i++){
		unsigned int n = ((pow(hd,i)-1)/(hd-1));//pow(hd, i) - 1;
		unsigned int k = ((pow(hd,i)-1)/(hd-1))*hd+1;//pow(hd, i) + 1;
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
		
		
		//update
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

	printf("%i %u %u %Le %Le\n", 0, swaps[0], e[0], times[0], (long double)0.0);	
	for(unsigned int j=1;j<swaps.size();j++){
		printf("%i %u %u %Le %Le\n", j, swaps[j], e[j], times[j]-times[j-1], (times[j]-times[j-1])/e[j]);
	}		
}


void test_insert(unsigned int hd){

	unsigned int n = pow(hd, NUM_EXP)-1; //limit
	unsigned int i=2;
	
	NHeap h(hd, n);
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
	
	printf("%i %u %u %Le %Le\n", 0, swaps[0], e[0], times[0], (long double)0.0);
	printf("%i %u %u %Le %Le\n", 1, swaps[1], e[1], times[1], (long double)0.0);	
	for(unsigned int j=2;j<swaps.size();j++){
		printf("%i %u %u %Le %Le\n", j, swaps[j], e[j], times[j]-times[j-1], (times[j]-times[j-1])/e[j]);
	}	
}


void test_scale(unsigned int hd){
	
	unsigned int n,m;

	Graph g = read_dimacs(std::cin, &n, &m);
	if(n <= 1)
		return;	
	int ninf = 0;
	for(unsigned int i=0;i<NUM_EXP;i++){
		
		
		size_t mu = 0;
		unsigned int n_ins, n_del, n_upd;
		unsigned int d;
		do{
    		int s = rand()%n;
    		int t = rand()%n;
    		while(s == t)
    			t = rand()%n;
			tstart = std::chrono::system_clock::now();
		    d = dijkstra_nheap_test(g, s, t, &n_ins, &n_del, &n_upd, &mu, hd);
		}while(d == MAX_DIST);
		
		tend = std::chrono::system_clock::now();
	
		elapsed_seconds = tend-tstart;	
		
		if(NUM_EXP != 1)
			printf("%u,", i);
				
		printf("%u,%u,%u,%u,%u,%lu,%Le,%u\n", n, m, n_ins, n_del, n_upd, mu, elapsed_seconds.count(), d);
		if(d == MAX_DIST)
			ninf++;
			
		//fprintf(stderr, "got\n");
	}
	
	fprintf(stderr, "ninf = %i\n", ninf);
		
}

void test_validate(unsigned int hd){
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
		
		unsigned int dst = dijkstra_nheap(g, s, t, hd);
		
		vector<unsigned int> dist(n);
  		vector<unsigned int> pred(n);
  		dijkstra_shortest_paths(g, s, weight_map(get(&EdgeData::weight,g)).distance_map(&dist[0]).predecessor_map(&pred[0]));
  		
  		int valid = 0;
  		if(dst != dist[t])
  			valid = -1;

		printf("%u,%u,%u,%i\n", i, dst, dist[t], valid);
	}

	return;
}


int main(int argc, char **argv){
	srand(time(0));
	
	unsigned int hd;
	char op;
	
	read_parameters(argc, argv, &op, &hd);

	swaps = vector<unsigned int>(NUM_EXP+1, 0);
	times = vector<long double>(NUM_EXP+1, 0.0);
	e = vector<unsigned int>(NUM_EXP+1, 0);

	if(op == 'i')
		test_insert(hd);
	else if(op == 'u')
		test_update(hd);
	else if(op == 'd')
		test_delete(hd);
	else if(op == 's')
		test_scale(hd);
	else if(op == 'v')
		test_validate(hd);
	else{
		fprintf(stderr, "Test option %c unknown.\n", op);
		usage(argv);
	}
	
}

void read_parameters(int argc, char **argv, char *op, unsigned int *hd){
	if(argc < 3){
		usage(argv);
		exit(-1);
	}
	bool has_type = false;
	*hd = 2;
	*op = 'z';
	
	for(int i=1;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 't':
					i++;
					*op = argv[i][0];
					has_type = true;
					break;
				case 'h':
					i++;
					*hd = atoi(argv[i]);
					break;
				case 'n':
					i++;
					NUM_EXP = atoi(argv[i]);
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
	
	if(!has_type){
		usage(argv);
		exit(-1);
	}
}

void usage(char **argv){
	fprintf(stderr, "usage:\n%s -t <test type> [-h <heap dimension>] [-n <number of tests>]\n\t-t test type: \t\ti, u, d, s, v\n\t-h heap dimension: \tnatural numbers\n\t-n number of tests: \tnatural numbers\n", argv[0]);
}

