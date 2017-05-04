#include "include/heap.h"
#include "include/nheap.h"
#include "include/hheap.hpp"
#include <cstdio>

void f(Heap& h){

    h.insert(4,6);
    
    printf("h -> %u,%u\n", h.getminKey(), h.getmin());

}


int main(){
    NHeap h(5);

    f(h)    ;
    printf("OK %u\n", h.getmin());
    
    return 0;

}



