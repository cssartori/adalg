#ifndef __CHRISGRAPH_H__
#define __CHRISGRAPH_H__

#include <vector>
#include <iostream>
#include <string>
#include <limits>


namespace Christofides{

    typedef long int Distance; //the type of the distance data
    
    //options to use the the Blossom V or the greedy algorithm to calculate a matching
    static const unsigned int BLOSSOM_COMPLETE_MAT_ALG = 1; //calls SolveComplete() : it is inefficient and uses for memory
    static const unsigned int BLOSSOM_SOLVE_MAT_ALG = 2; //calls Solve() : more efficient, less memory, but may not finish (appears to have some bug)
    static const unsigned int GREEDY_MAT_ALG = 3; //Calculates an approximation to the perfect matching with an efficient greedy algorithm
    static const unsigned int DEFAULT_MAT_ALG = BLOSSOM_SOLVE_MAT_ALG;
    static const double DEFAULT_GREEDY_P = 1.5;
        
    static const Distance MAX_WEIGHT = std::numeric_limits<Distance>::max(); 
    
    enum DistType{ EUC_2D = 1024, EUC_3D, MAX_2D, MAX_3D, MAN_2D, MAN_3D,
                     CEIL_2D, GEO }; //the type of calculation to find the distance
    
    //struct of a graph/instance
    struct ChrisGraph{
        //3 vectors allow up to 3 dimension instances
        std::vector<double> px;
        std::vector<double> py;
        std::vector<double> pz;
        
        DistType dtype; //distance type of the graph
        //general information of the instance
        std::string name, type, comment, edge_weight_type, edge_weight_format, 
                           edge_data_format, node_coord_type, display_data_type;
                                              
        unsigned int dim; //dimension of the problem (num nodes)
        
        //returns the distance between two nodes according to the distance computation given in the input file
        Distance dist(unsigned int i, unsigned int j) const;
    };
    
    struct TSPSolution{
        std::vector<unsigned int> perm; //permutation of nodes to be visited
        Distance cost; //total cost of the solution
    };
    
    //read the input stream into a graph for chirstofides algorithm    
    unsigned int read_instance(ChrisGraph& g, std::istream& f);
    
    //runs christofides algorithm to get an approximation of a TSP solution
    Distance run_christofides(const ChrisGraph& g, int opmat=DEFAULT_MAT_ALG, double p=DEFAULT_GREEDY_P);
}

#endif //__CRISGRAPH_H__
