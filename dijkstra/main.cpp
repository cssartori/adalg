#include "nheap.h"
#include <cstdio>


int main(){
	NHeap h(2,201,201);
	
	for(int i=0;i<100;i++){
		h.insert(200-i,200-i);
	}
	
//	for(int i=0;i<200;i++){
//		printf("%i\n", h.getmin());
//		h.deletemin();
//	}
	
	return 0;
}
