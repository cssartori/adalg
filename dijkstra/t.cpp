#include "include/hheap.hpp"
#include <cstdio>

int main(){
    const int N = 100;
    HHeap h;
    
    unsigned int *u = (unsigned*)malloc(sizeof(unsigned)*N);
    for(int i=0;i<N;i++){
        u[i] = i;
        h.insert(&u[i], 5*N-i);
    }
       
//    for(int i=0;i<N;i++){
//        h.update_key(&u[i], i);
//    }
    
//    unsigned int *u = (unsigned*)malloc(sizeof(unsigned)*3);
//    u[0] = 0; u[1] = 1; u[2] = 2;
//    h.insert(&u[0],100);
//    h.insert(&u[1],200);
//    h.insert(&u[2],300);
//    
//    h.print_roots();
//   // h.update_key(&u[0], 300);
//    h.update_key(&u[1], 10);
//    h.update_key(&u[2], 5);
    
    printf("nt = %u\nne = %u\n", h.getnt(), h.getne());
    
 //   h.print_roots();
    
    while(!h.is_empty()){
        printf("%u\n", *h.getmin());
        h.delete_min();
    }
    printf("nt = %u\nne = %u\n", h.getnt(), h.getne());
    printf("Done.\n");

    return 0;
}
