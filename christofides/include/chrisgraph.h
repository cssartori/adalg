#ifndef __CHRISGRAPH_H__
#define __CHRISGRAPH_H__

#include <vector>
#include <iostream>
#include <string>
#include <limits>


namespace Christofides{

    typedef unsigned int Distance; //the type of the distance data
    typedef std::vector< std::vector<unsigned int> > MST; //minimum spanning tree of a graph is an adjacency list
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
    
    //read the input stream into a graph for chirstofides algorithm    
    unsigned int read_instance(ChrisGraph& g, std::istream& f);
    
    //runs christofides algorithm to get an approximation of a TSP solution
    Distance chris_algorithm(const ChrisGraph& g);
}

#endif //__CRISGRAPH_H__
