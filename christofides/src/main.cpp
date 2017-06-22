#include <cstdio>
#include <iostream>
#include "../include/chrisgraph.h"

using namespace std;
using namespace Christofides;

int main(){

    ChrisGraph g;
    
    if(read_instance(g, std::cin) != 0){
        cout << "Error reading input file\n";
        return -1;
    }

    //cout << "Read input file...\n";
    
    Distance d = chris_algorithm(g);
    
    //cout << "Christofides algorithm finished with " << d << endl;
    cout << d << endl;
    
    return 0;
}
