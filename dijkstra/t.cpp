#include "include/hheap.hpp"
#include <cstdio>

int main(){

    HHeap h;
    
    for(int i=0;i<100;i++){
        unsigned int *u = (unsigned*)malloc(sizeof(unsigned));
        *u = 100-i;
        h.insert(u, 100-i);
    }
    
//    unsigned int *u = (unsigned*)malloc(sizeof(unsigned)*3);
//    u[0] = 0; u[1] = 1; u[2] = 2;
//    h.insert(&u[0],0);
//    h.insert(&u[1],1);
//    h.insert(&u[2],2);
//    
    printf("nt = %u\nne = %u\n", h.getnt(), h.getne());
    
   // h.print_roots();
    
    while(!h.is_empty()){
        printf("%u\n", *h.getmin());
        h.delete_min();
    }
    printf("nt = %u\nne = %u\n", h.getnt(), h.getne());
    printf("Done.\n");

    return 0;
}
