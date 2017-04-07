#include <cstdio>
#include <chrono>
#include <math.h>
#include <vector>
#include "../include/nheap.h"
#include "../include/dgraph.h"

unsigned int NUM_EXP = 20;

using namespace std;

vector<unsigned int> swaps(NUM_EXP+1, 0);
vector<double> times(NUM_EXP+1, 0.0);
vector<unsigned int> e(NUM_EXP+1, 0.0);

std::chrono::time_point<std::chrono::system_clock> tstart, tend;
std::chrono::duration<double> elapsed_seconds;


void read_parameters(int argc, char **argv, char *op, int *hd);
void usage(char **argv);

void test_delete(int hd){
	NHeap h(hd, pow(2, NUM_EXP)+1);
	
	for(unsigned int i=1;i<=NUM_EXP;i++){
		int N = pow(2, i) - 1;
		int n = N;
		
		while(n > 0){
			n--;
			h.insert(rand()%N, n);
		}

	   	tstart = std::chrono::system_clock::now();
		h.n_swaps = 0;
		while(n < N){
			n++;	
			h.deletemin();
		}
		
		tend = std::chrono::system_clock::now();
		elapsed_seconds = tend-tstart;	
		
		swaps[i] = h.n_swaps;
		times[i] = elapsed_seconds.count();
	}
	
	printf("%i,%u,%u,%lf\n", 0, swaps[0], e[0], times[0]);	
	for(unsigned int j=1;j<swaps.size();j++){
		printf("%i,%u,%u,%lf\n", j, swaps[j], e[j], times[j]-times[j-1]);
	}	
}

void test_update(int hd){
	
	for(unsigned int i=1;i<=NUM_EXP;i++){
		unsigned int n = pow(2, i) - 1;
		unsigned int k = pow(2, i) + 1;
		unsigned int el = 0;
		
		NHeap h(hd, n*2+1);
				
		for(unsigned int x=0;x<n;x++)
			h.insert(k, el++);
		
		n = n+1;
		k = k+1;
		
		vector<unsigned int> els;
		for(unsigned int x=0;x<n;x++){
			h.insert(k, el);
			els.push_back(el);
			el++;
		}
		
		
		h.n_swaps = 0;
		k = k-2;

	   	tstart = std::chrono::system_clock::now();	
		
		for(unsigned int x=0;x<n;x++){
			h.update_key(els[x], k--);	
		}

	   	tend = std::chrono::system_clock::now();
		elapsed_seconds = tend-tstart;			
		
		swaps[i] = h.n_swaps;
		times[i] = elapsed_seconds.count();
		e[i] = (i)*pow(2, i);
	}

	printf("%i,%u,%u,%lf\n", 0, swaps[0], e[0], times[0]);	
	for(unsigned int j=1;j<swaps.size();j++){
		printf("%i,%u,%u,%lf\n", j, swaps[j], e[j], times[j]-times[j-1]);
	}	
}


void test_insert(int hd){

	unsigned int n = pow(hd, NUM_EXP)-1; //limit
	unsigned int i=2;
	
	NHeap h(hd, n);
	h.insert(n, n);
	
	h.n_swaps = 0;
	n--;
	unsigned int ninserts = 1;

   	tstart = std::chrono::system_clock::now();
   	unsigned int NI = pow(hd,i)-1;
   	
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
			NI = ((NI+1)*hd)-1;
		}
	}
	
	printf("%i,%u,%u,%lf\n", 0, swaps[0], e[0], times[0]);	
	for(unsigned int j=1;j<swaps.size();j++){
		printf("%i,%u,%u,%lf\n", j, swaps[j], e[j], times[j]-times[j-1]);
	}	
}


void test_scale(int hd){
	
	unsigned int n,m;

	Graph g = read_dimacs(std::cin, &n, &m);
	if(n <= 1)
		return;	

	for(unsigned int i=0;i<NUM_EXP;i++){
		int s = rand()%n;
		int t = rand()%n;
		while(s == t)
			t = rand()%n;
		
		tstart = std::chrono::system_clock::now();
		size_t mu = 0;
		dijkstra_nheap_mem(g, s, t, &mu, hd);
		tend = std::chrono::system_clock::now();
	
		elapsed_seconds = tend-tstart;	
		
		if(NUM_EXP != 1)
			printf("%u,", i);
				
		printf("%lu,%f\n", mu, elapsed_seconds.count());
	}
		
}

int main(int argc, char **argv){
	srand(time(0));
	
	int hd = 2;
	char op = 'z';
	
	read_parameters(argc, argv, &op, &hd);

	if(op == 'i')
		test_insert(hd);
	else if(op == 'u')
		test_update(hd);
	else if(op == 'd')
		test_delete(hd);
	else if(op == 's')
		test_scale(hd);
	else{
		fprintf(stderr, "Test option %c unknown.\n", op);
		usage(argv);
	}
	
}

void read_parameters(int argc, char **argv, char *op, int *hd){
	if(argc < 3){
		usage(argv);
		exit(-1);
	}
	bool has_type = false;
	
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
	fprintf(stderr, "usage:\n%s -t <test type> [-h <heap dimension>] [-n <number of tests>]\n\t-t test type: \t\ti, u, d, s\n\t-h heap dimension: \tnatural numbers\n\t-n number of tests: \tnatural numbers\n", argv[0]);
}

