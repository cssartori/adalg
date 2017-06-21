#include <cstdio>
#include <iostream>
#include "../include/crisgraph.h"

using namespace std;
using namespace Cristofides;

int main(){

    CrisGraph g;
    
    if(read(g, std::cin) != 0){
        cout << "Error reading input file\n";
        return -1;
    }

    cout << "Read input file...\n";
    
    MST mt = findMST(g);
    
    cout << "Created MST\n";

    findMatching(mt);

    cout << "Matching found\n";
}
