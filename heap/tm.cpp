#include "include/heap.h"
#include "include/nheap.h"
#include "include/hheap.hpp"
#include <cstdio>

void f(Heap& h){

    for(int i=0;i<100;i++){
        h.insert(i,i+1000);
    }

    for(int i=50;i<100;i++){
        h.update_key(i, 100+i+1);
    }

    while(!h.is_empty()){
        printf("%u,%u\n", h.getmin(),h.getminKey());
        h.deletemin();
    }
    
//    printf("h -> %u,%u\n", h.getminKey(), h.getmin());

}


int main(){
    NHeap h(1000);

    f(h)    ;
    printf("OK\n");
    
    return 0;

}



