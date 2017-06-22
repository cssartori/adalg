#include <cstdio>
#include <iostream>
#include "../include/chrisgraph.h"

using namespace std;
using namespace Christofides;

int main(){

    ChrisGraph g;
    
    if(read(g, std::cin) != 0){
        cout << "Error reading input file\n";
        return -1;
    }

    cout << "Read input file...\n";
    
    MST mt = findMST(g);
    
    cout << "Created MST\n";

    findMatching(mt, g);

    cout << "Matching found\n";
}
