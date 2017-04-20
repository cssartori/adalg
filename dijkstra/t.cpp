#include "include/hheap.hpp"
#include <cstdio>

int main(){

    HHeap h;
    
    for(int i=0;i<100;i++){
        unsigned int *u = (unsigned*)malloc(sizeof(unsigned));
        *u = 100-i;
        h.insert(u, 100-i);
    }
    
    printf("nt = %u\nne = %u\n", h.getnt(), h.getne());
    
    h.print_roots();
//    
//    for(int i=0;i<100;i++){
//        printf("%u\n", *h.getmin());
//        h.delete_min();
//    }
    
    printf("Done.\n");

    return 0;
}
