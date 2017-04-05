#include <cstdio>
#include "nheap.h"
#include <chrono>
#include <math.h>
#include <vector>

const int NUM_EXP = 25;

using namespace std;

vector<unsigned int> swaps(NUM_EXP+1, 0);
vector<double> times(NUM_EXP+1, 0.0);
vector<unsigned int> e(NUM_EXP+1, 0.0);


void test_delete(){
	srand(time(0));
	
	NHeap h(2, pow(2, NUM_EXP)+1);
	
	for(int i=1;i<=NUM_EXP;i++){
		int N = pow(2, i) - 1;
		int n = N;
		
		while(n > 0){
			n--;
			h.insert(rand()%N, n);
			
			
		}	
	}
	
}

void test_update(){

	for(int i=1;i<=NUM_EXP;i++){
		int n = pow(2, i) - 1;
		int k = pow(2, i) + 1;
		int el = 0;
		
		NHeap h(2, n*2+1);
		h.insert(k, el++);
		
		for(int x=0;x<n-1;x++)
			h.insert(k, el++);
		
		n = n+1;
		k = k+1;
		
		vector<int> els;
		for(int x=0;x<n;x++){
			h.insert(k, el++);
			els.push_back(el);
		}
		
		h.n_swaps = 0;
		k = k-2;
		std::chrono::time_point<std::chrono::system_clock> start, end;
	   	start = std::chrono::system_clock::now();	
		
		for(int x=0;x<els.size();x++)
			h.update_key(k--, els[x]);	
		
	   	end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end-start;			
		
		swaps[i] = h.n_swaps;
		times[i] = elapsed_seconds.count();
		e[i] = i*pow(2, i);
	}

}


void test_insert(){

	unsigned int n = pow(2, NUM_EXP)-1; //limit
	unsigned int i=2;
	
	NHeap h(2, n);
	h.insert(n, n);
	
	h.n_swaps = 0;
	n--;
	unsigned int ninserts = 1;
	std::chrono::time_point<std::chrono::system_clock> start, end;
   	start = std::chrono::system_clock::now();
   	unsigned int NI = pow(2,i)-1;
   	
	for(;n > 0 && i < NUM_EXP+1;n--){
		h.insert(n, n);
		ninserts++;
		if(NI == ninserts){
			swaps[i] = h.n_swaps;
		   	end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;			
			times[i] = elapsed_seconds.count();
			e[i] = (i-1)*pow(2,i-1);
			i++;
			NI = ((NI+1)*2)-1;
		}
	}

}



int main(int argc, char **argv){

	if(argc < 2){
		printf("usage: %s [test type]\n", argv[0]);
		return 0;
	}
	
	char tt = argv[1][0];	
	
	if(tt == 'i')
		test_insert();
	else if(tt == 'u')
		test_update();
	else if(tt == 'd')
		test_delete();
	
	printf("%i \t\t%u\t\t%u\t\t%lf\n", 0, swaps[0], e[0], times[0]);	
	for(int j=1;j<swaps.size();j++){
		printf("%i \t\t%u\t\t%u\t\t%lf\n", j, swaps[j]-swaps[j-1], e[j], times[j]-times[j-1]);
	}	

}

