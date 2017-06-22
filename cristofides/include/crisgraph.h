#ifndef __CRISGRAPH_H__
#define __CRISGRAPH_H__

#include <vector>
#include <iostream>
#include <string>
#include <limits>


namespace Cristofides{

    typedef unsigned int Distance; //the type of the distance data
    typedef std::vector< std::vector<unsigned int> > MST; //minimum spanning tree of a graph is an adjacency list
    static const Distance MAX_WEIGHT = std::numeric_limits<Distance>::max(); 
    
    enum DistType{ EUC_2D = 1024, EUC_3D, MAX_2D, MAX_3D, MAN_2D, MAN_3D,
                     CEIL_2D, GEO}; //the type of calculation to find the distance
    
    //struct of a graph/instance
    struct CrisGraph{
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
    
    //read the specification area of the input stream
    unsigned int read_specification(CrisGraph& g, std::istream& f);
    
    //read the data part of the input stream
    unsigned int read_data(CrisGraph& g, std::istream& f);
    
    //read the input stream into a graph for chirstofides algorithm    
    unsigned int read(CrisGraph& g, std::istream& f);
    
    //find a MST in the graph
    MST findMST(const CrisGraph& g);

    //find a matching in the mst generated from the input graph
    void findMatching(const MST& mt);
}

#endif //__CRISGRAPH_H__
