#include <cstdio>
#include "nheap.h"
#include <chrono>
#include <math.h>
#include <vector>

const int NUM_EXP = 20;

using namespace std;

vector<int> swaps(NUM_EXP+1, 0);
vector<double> times(NUM_EXP+1, 0.0);
vector<double> e(NUM_EXP+1, 0.0);


void test_delete(){
	srand(time(0));
	
	NHeap h(2);
	
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
		
		NHeap h(2, k, el++);
		
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
		e[i] = pow(2, i)*i;
	}

}


void test_insert(){

	int n = pow(2, NUM_EXP)-1; //limit
	int i=2;
	
	NHeap h(2, n);
	h.insert(n, n);
	
	h.n_swaps = 0;
	n--;
	int ninserts = 1;
	std::chrono::time_point<std::chrono::system_clock> start, end;
   	start = std::chrono::system_clock::now();
   	
	for(int n=pow(2, NUM_EXP)-1;n > 0 && i < NUM_EXP+1;n--){
		h.insert(n, n);
		ninserts++;
		if(pow(2, i)-1 == ninserts){
			swaps[i] = h.n_swaps;
			//h.n_swaps = 0;
		   	end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;			
			times[i] = elapsed_seconds.count();
			e[i] = e[i-1] + (i-1)*pow(2,i-1); //pow(2,i)*(log(i+1)/log(2));
			i++;
		}
	}

}





int main(int argc, char **argv){

	if(argc < 2){
		printf("usage: %s [test type]\n");
		return 0;
	}
	
	char tt = argv[1];	
	
	if(tt == 'i')
		test_insert();
	else if(tt == 'u')
		test_update();
	else if(tt == 'd')
		test_delete();
	
			
	for(int j=0;j<swaps.size();j++){
		printf("%i\ts = %i | e = %.2f\t\tt=%.2f\n", j, swaps[j], e[j], times[j]);
	}	

}

