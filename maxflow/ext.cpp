/**
 * \file maxflow.cpp
 *   \author Marcus Ritt <mrpritt@inf.ufrgs.br> 
 *   \version $Id: emacs 2872 2009-01-31 01:46:50Z ritt $
 *   \date Time-stamp: <2015-09-22 21:17:31 ritt>
 *
 * Read a maximum flow problem in DIMACS format and output the maximum flow.
 *
 */
#include <iostream>
#include <cstring>
using namespace std;
 
#include "include/dgraph.h" 
 
int main(int argc, char *argv[]) {
    Graph gr;
    unsigned n;
    unsigned m;
    unsigned s;
    unsigned t;

    gr = read_dimacs_max_flow(gr, std::cin, &n,&m,&s,&t);
    unsigned int fat = fattest_path(gr, s, t);
    cout << fat << endl;

    return fat;    
}
