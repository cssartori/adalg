#include "../include/chrisgraph.h"
#include "../../heap/include/heap.h"
#include "../../heap/include/nheap.h"
#include "../blossomv/PerfectMatching.h"
#include "../blossomv/GEOM/GeomPerfectMatching.h"
#include <cmath>
#include <list>
#include <stack>
#include "../../common/cc_gv.h"
        #include <map>

using namespace std;

namespace Christofides{
    
    //typedef std::vector< std::vector<unsigned int> > MST; //minimum spanning tree of a graph is an adjacency list
    static const unsigned int NULL_NODE = std::numeric_limits<unsigned int>::max();
        
    struct MST{
        std::vector< std::list<unsigned int> > g; //graph of the mst
        unsigned int nedges;
        unsigned int nnodes;
        Distance cost;
    };
    
    Distance ChrisGraph::dist(unsigned int i, unsigned int j) const{
            if(i == j) return Distance(0);
            double xd, yd, zd;
            double q1, q2, q3;
            const double RRR = 6378.388;
            switch(this->dtype){
                case EUC_2D:
                    xd = this->px[i] - this->px[j];
		            yd = this->py[i] - this->py[j];
		            return lrint(sqrt(xd*xd+yd*yd));
		        case EUC_3D:
		            xd = this->px[i] - this->px[j];
		            yd = this->py[i] - this->py[j];
		            zd = this->pz[i] - this->pz[j];
		            return lrint(sqrt(xd*xd+yd*yd+zd*zd));
		        case MAX_2D:
		            xd = this->px[i] - this->px[j];
		            yd = this->py[i] - this->py[j];
		            return std::max(lrint(xd), lrint(yd));
		        case MAX_3D:
		            xd = this->px[i] - this->px[j];
		            yd = this->py[i] - this->py[j];
		            zd = this->pz[i] - this->pz[j];
		            return std::max(lrint(zd), std::max(lrint(xd), lrint(yd)));
		        case MAN_2D:
		       		xd = abs(this->px[i] - this->px[j]);
		            yd = abs(this->py[i] - this->py[j]);
		            return lrint(xd+yd);            
		        case MAN_3D:
		       		xd = abs(this->px[i] - this->px[j]);
		            yd = abs(this->py[i] - this->py[j]);
		            zd = abs(this->pz[i] - this->pz[j]);
		            return lrint(xd+yd+zd);            
		        case CEIL_2D:
		            xd = this->px[i] - this->px[j];
		            yd = this->py[i] - this->py[j];
		            return Distance(ceil(sqrt(xd*xd+yd*yd)));
		        case GEO:
		            q1 = cos(this->py[i] - this->py[j]);
		            q2 = cos(this->px[i] - this->px[j]);
		            q3 = cos(this->px[i] + this->px[j]);
		            return Distance(RRR * acos(0.5*((1.0+q1)*q2-(1.0-q1)*q3))+1.0);
		        default:
		            throw std::string("Invalid distance type ")+this->type+std::string(" \n");
        }
    }
    
    
    //read keywords from the stream (separated by spaces)
    std::string read_keyword(std::istream& f) {
        std::string keyword;
        if (f >> keyword)
            return keyword;
        else
            throw "EOF";
    }
    
    //skip the separator : in the stream
    void skip_separator(std::istream& f) {
        std::string sep;
        f >> sep;
        if (sep != ":") //separator is a ":"
            throw "Expected separator : but found \'"+sep+"\'";
    }
    
    
    //convert x,y input to lat,long input
    std::pair<double,double> latlong(double x, double y){
        double deg = lrint(x);
        double min = x - deg;
        double lat = M_PI * (deg + 5.0 * min / 3.0 ) / 180.0;
        deg = lrint(y);
        min = y - deg;
        double lon = M_PI * (deg + 5.0 * min / 3.0 ) / 180.0; 
        
        return std::make_pair(lat, lon);
    }
    
       
    //read the specification area of the input stream
    unsigned int read_specification(ChrisGraph& g, std::istream& f){
        std::string keyword;
        g.node_coord_type = "TWOD_COORDS";
        
        do {
            keyword = read_keyword(f);
            if (keyword[keyword.length()-1] == ':') {
                keyword = keyword.substr(0,keyword.length()-1);
                f.putback(':');
            }   
    
            if(keyword == "NAME"){
                skip_separator(f);
                f >> g.name;
            }else if(keyword == "TYPE"){
                skip_separator(f);
                f >> g.type;
                if( g.type != "TSP"&& g.type != "ATSP" && g.type != "SOP" && g.type != "HCP" && g.type != "CVRP" && g.type != "TOUR"){
                    throw "Unknown instance type \""+g.type+"\"\n";
                    return -1;
                }
            }else if(keyword == "COMMENT"){
                skip_separator(f);
                char cline[1024];
                f.getline(cline,1024);
                g.comment = cline;
            }else if(keyword == "DIMENSION"){
                skip_separator(f);
                f >> g.dim;
            }else if(keyword == "CAPACITY"){
                skip_separator(f);
                unsigned int cap;
                f >> cap;
                throw "Found capacity. What to do?\n";
                return -1;
            }else if(keyword == "EDGE_WEIGHT_TYPE"){
                skip_separator(f);
                f >> g.edge_weight_type;
                if(g.edge_weight_type == "EUC_2D")
                    g.dtype = EUC_2D;
                else if(g.edge_weight_type == "EUC_3D")
                    g.dtype = EUC_3D;
                else if(g.edge_weight_type == "MAX_2D")
                    g.dtype = MAX_2D;
                else if(g.edge_weight_type == "MAX_3D")
                    g.dtype = MAX_3D;
                else if(g.edge_weight_type == "MAN_2D")
                    g.dtype = MAX_2D;
                else if(g.edge_weight_type == "MAN_3D")
                    g.dtype = MAN_3D;
                else if(g.edge_weight_type == "CEIL_2D")
                    g.dtype = CEIL_2D;
                else if(g.edge_weight_type == "GEO")
                    g.dtype = GEO;    
                else{
                    throw std::string("Unkown edge weight type ")+g.edge_weight_type;
                    return -1;
                }
            }else if(keyword == "EDGE_WEIGHT_FORMAT"){
                skip_separator(f);
                f >> g.edge_weight_format;
            }else if(keyword == "EDGE_DATA_FORMAT"){
                skip_separator(f);
                f >> g.edge_data_format;
            }else if(keyword == "NODE_COORD_TYPE"){
                skip_separator(f);
                f >> g.node_coord_type;
            }else if(keyword == "DISPLAY_DATA_TYPE"){
                skip_separator(f);
                f >> g.display_data_type;
            }else if (keyword == "EOF"){
                skip_separator(f);
            }else {
              return 0;
            }
        } while (true);
    }
       
    //read the data part of the input stream
    unsigned int read_data(ChrisGraph& g, std::istream& f){
        //allocate memory
        g.px.assign(g.dim, 0.0);
        g.py.assign(g.dim, 0.0);
        if(g.node_coord_type == "THREED_COORDS")
            g.pz.assign(g.dim, 0.0);
            
        std::string keyword = "NODE_COORD_SECTION";
        
        try {
            do {
                if (keyword == "NODE_COORD_SECTION") {
	                if (g.node_coord_type == "TWOD_COORDS") {
	                    // get coordinates
	                    for(unsigned int i=0; i<g.dim; i++) {
	                        unsigned int j;
	                        double x,y;
	                        f >> j >> x >> y;
	                        if(g.dtype != GEO){
	                            g.px[j-1] = x;
	                            g.py[j-1] = y;
	                        }else{
	                            std::pair<double,double> ll = latlong(x,y);
	                            g.px[j-1] = ll.first;
	                            g.py[j-1] = ll.second;
	                        } 
	                    }                   	                
	                }else if (g.node_coord_type == "THREED_COORDS") {
	                    // get coordinates
	                    for(unsigned int i=0; i<g.dim; i++) {
	                        unsigned int j;
	                        double x,y,z;
	                        f >> j >> x >> y >> z;
                            g.px[j-1] = x;
	                        g.py[j-1] = y;
	                        g.pz[j-1] = z;
	                    }                   	                
	                }else 
	                    throw std::string("Unsupported coordinate type ")+g.node_coord_type;
                }else if (keyword == "DEPOT_SECTION") {
                	throw std::string("Unsupported data section ")+keyword;
                }else if (keyword == "DEMAND_SECTION") {
	                throw std::string("Unsupported data section ")+keyword;
                }else if (keyword == "EDGE_DATA_SECTION") {
	                throw std::string("Unsupported data section ")+keyword;
                }else if (keyword == "FIXED_EDGES_SECTION") {
	                throw std::string("Unsupported data section ")+keyword;
                }else if (keyword == "DISPLAY_DATA_SECTION") {
	                throw std::string("Unsupported data section ")+keyword;
                }else if (keyword == "TOUR_SECTION") {
	                throw std::string("Unsupported data section ")+keyword;
                }else if (keyword == "EDGE_WEIGHT_SECTION") {
		            throw std::string("Unsupported data section ")+keyword;    
                }else if (keyword == "EOF") {
                	return 0;
                }else if (keyword == "" && f.eof()) {
	                return 0;
                }else
                    throw "Unknown keyword \""+keyword+"\"";
                    
                keyword = read_keyword(f);
            }while (true);
        }catch (const std::string& s) {
            std::cout << s << std::endl;
            return -1;
        }catch (...) {
            std::cout << "Warning: Unexpected end of file while scanning for keyword." << std::endl;
            return -1;
        }
    }
    
    //read the input stream into a graph for chirstofides algorithm    
    unsigned int read_instance(ChrisGraph& g, std::istream& f){
        try{
            if(read_specification(g, f) != 0){
                std::cout << "Error reading specification of input file\n" << std::endl;
                return -1;
            }
            
            if(read_data(g, f) != 0){
                std::cout << "Error reading data of input file\n" << std::endl;
                return -1;
            }
        }catch(const std::string& s){
            std::cout << s << std::endl;
            return -1;
        }
        
        return 0;
    }
    
       
    //find a MST in the graph
    MST find_mst(const ChrisGraph& g){
        std::vector<bool> visited(g.dim, false);
        std::vector<unsigned int> prev(g.dim, NULL_NODE); //the previous of each node in the MST construction
        std::vector<Distance> weight(g.dim, MAX_WEIGHT);
        
        NHeap h(g.dim, 4);
        weight[0] = 0; //starting at node 0 (graph is complete, does not make much difference)
        h.insert(0, weight[0]);
        for(unsigned int u=1;u<g.dim;u++)
            h.insert(u,weight[u]);
        
        while(not h.is_empty()){
            unsigned int u = h.gettop();
            h.deletetop();
            visited[u] = true;
            for(unsigned int v=0;v<g.dim;v++){                
                if(not visited[v] && g.dist(u,v) < weight[v]){
                    h.update_key(v, g.dist(u,v));
                    weight[v] = g.dist(u,v);
                    prev[v] = u;
                }
            }
        }

        //build MST   
        MST mt;
        mt.g.assign(g.dim, std::list<unsigned int>());
        mt.nnodes = g.dim;
        mt.nedges = 0;
        mt.cost = 0;     
        for(unsigned int u=1;u<g.dim;u++){
            mt.g[u].push_back(prev[u]);
            mt.g[prev[u]].push_back(u);    
            mt.cost += g.dist(u, prev[u]);
            mt.nedges += 1;
        }
        
        return mt;
    }
    
    MST blossom_matching(std::vector<unsigned int>& oddn, const MST& mt, const ChrisGraph& g){
        unsigned int dimension = g.pz.size() > 0 ? 3 : 2;
        GeomPerfectMatching gpm(oddn.size(), dimension);
        
        vector<double*> ps(oddn.size(), nullptr); //vector of points in order to not lose the references
        for(unsigned int i=0;i<oddn.size();i++){
            ps[i] = new double[dimension];
            ps[i][0] = g.px[oddn[i]];
            ps[i][1] = g.py[oddn[i]];
            if(dimension > 2)
                ps[i][3] = g.pz[oddn[i]];
            
            gpm.AddPoint(ps[i]);
        }
        //cout << "Solving blossom v\n";          
        gpm.SolveComplete();
        //gpm.Solve();
       // cout << "Solved blossom v\n";      
        //unite matching and MST
        MST meuler = mt;
        for(unsigned int i=0;i<oddn.size();i++){
            if(oddn[i] == NULL_NODE) continue;
            unsigned int j=gpm.GetMatch(i);
            meuler.g[oddn[i]].push_back(oddn[j]);
            meuler.g[oddn[j]].push_back(oddn[i]);    
            meuler.nedges += 1;
            meuler.cost += g.dist(oddn[i],oddn[j]);   
            oddn[i] = NULL_NODE;
            oddn[j] = NULL_NODE;
            delete [] ps[i];
            ps[i] = nullptr;
        }        

//          //Old code
//        PerfectMatching pm(oddn.size(), oddn.size()*oddn.size());
//        for(unsigned int i=0;i<oddn.size();i++)
//            for(unsigned int j=i+1;j<oddn.size();j++)
//                pm.AddEdge(i,j,g.dist(oddn[i],oddn[j]));
//                       
//        pm.Solve();
//        
//        //unite matching and MST
//        MST meuler = mt;
//        int edge = 0;
//        for(unsigned int i=0;i<oddn.size();i++){
//            for(unsigned int j=i+1;j<oddn.size();j++){
//                if(pm.GetSolution(edge)){
//                    meuler.g[oddn[i]].push_back(oddn[j]);
//                    meuler.g[oddn[j]].push_back(oddn[i]);    
//                    meuler.nedges += 1;
//                    meuler.cost += g.dist(oddn[i],oddn[j]);
//                }
//                edge++;
//            }
//        }
        
        return meuler;
    }
    
    MST greedy_matching(const std::vector<unsigned int>& oddn, const MST& mt, const ChrisGraph& g){
        vector<unsigned int> mates(g.dim, NULL_NODE);
        unsigned int matched = 0;
        
        #define GCACHE 1
        
        #if GCACHE

        map< pair<unsigned , unsigned>, bool > paired;
        vector< vector< pair<unsigned int, Distance> > > maxed(oddn.size(), vector<pair<unsigned int, Distance> >());
        unsigned int NE = std::min((size_t)400,oddn.size()-1);
        for(unsigned int i=0;i<oddn.size();i++){
            maxed[i].reserve(NE);
            Distance maxn = 0;
            //if(mates[oddn[i]] != NULL_NODE) continue;
            for(unsigned int j=0;j<oddn.size();j++){
                if(i == j) continue;
                if(paired.count(make_pair(j,i)) > 0 && paired[make_pair(j,i)]
                    
                ) continue;
                //if(mates[oddn[j]] != NULL_NODE) continue;
                Distance d = g.dist(oddn[i], oddn[j]);
                if(maxed[i].size() < NE-1){
                    maxed[i].push_back(make_pair(j,d));
                    if(d > maxn)
                        maxn = d;
                    paired[make_pair(i,j)] = true;
                }else if(d < maxn){
                                            
                    Distance maxd = 0;
                    unsigned int l=0;
                    for(unsigned int k=0;k<NE;k++){
                        if(maxed[i][k].second > maxd)
                            l = k;
                    }
                    
                    if(d < maxd){
                        paired[make_pair(i,j)] = true;
                        paired[make_pair(i,maxed[i][l].first)] = false;
                        maxed[i][l].first = j;
                        maxed[i][l].second = d;
                    }
                }  
            }
        }
        
        
        unsigned cc = 0;
        while(matched < oddn.size()){
            unsigned int u = NULL_NODE;
            unsigned int v = NULL_NODE;
            Distance maxcost = MAX_WEIGHT;

            for(unsigned int i=0;i<oddn.size();i++){
                if(mates[oddn[i]] != NULL_NODE) continue;
                for(unsigned int j=0;j<maxed[i].size();j++){
                    if(mates[oddn[maxed[i][j].first]] != NULL_NODE) continue;
                    
                    if(maxed[i][j].second < maxcost){
                        u = oddn[i];
                        v = oddn[maxed[i][j].first];
                        maxcost = maxed[i][j].second;
                    }
                }
            }
            
            if(u == NULL_NODE || v == NULL_NODE){
                cc++;
                for(unsigned int i=0;i<oddn.size();i++){
                    if(mates[oddn[i]] != NULL_NODE) continue;
                    for(unsigned int j=i+1;j<oddn.size();j++){
                        if(mates[oddn[j]] != NULL_NODE) continue;
                        if(g.dist(oddn[i], oddn[j]) < maxcost){
                            u = oddn[i];
                            v = oddn[j];
                            maxcost = g.dist(oddn[i], oddn[j]);
                        }
                    }
                }
            }
            
            mates[u] = v;
            mates[v] = u;
            matched+=2;
        }
        matched = 0;
        printf("called %u times instead of %u\n", cc, oddn.size());

        #endif
        
        #if !GCACHE
        //Complexity O(n^3)
        //TODO: improve code by using a type of cache        
        while(matched < oddn.size()){
            unsigned int u = NULL_NODE;
            unsigned int v = NULL_NODE;
            Distance maxcost = MAX_WEIGHT;

            for(unsigned int i=0;i<oddn.size();i++){
                if(mates[oddn[i]] != NULL_NODE) continue;
                for(unsigned int j=i+1;j<oddn.size();j++){
                    if(mates[oddn[j]] != NULL_NODE) continue;
                    if(g.dist(oddn[i], oddn[j]) < maxcost){
                        u = oddn[i];
                        v = oddn[j];
                        maxcost = g.dist(oddn[i], oddn[j]);
                    }
                }
            }
            
            mates[u] = v;
            mates[v] = u;
            matched+=2;
        }
        #endif
        
        //unite matching and MST
        MST meuler = mt;
        for(unsigned int i=0;i<oddn.size();i++){
            if(mates[oddn[i]] == NULL_NODE) continue;    
            
            unsigned int u = oddn[i];
            unsigned int v = mates[oddn[i]];
            meuler.g[u].push_back(v);
            meuler.g[v].push_back(u);    
            meuler.nedges += 1;
            meuler.cost += g.dist(u,v);
            
            mates[u] = NULL_NODE;
            mates[v] = NULL_NODE;   
        }
        
        return meuler;
    }
    
    //find an Eulerian Graph with the mst generated from the input graph and a matching subgraph
    MST find_eulerian_graph(const MST& mt, const ChrisGraph& g, int opmat = BLOSSOM_MAT_ALG){
        std::vector<unsigned int> oddn; // nodes with odd number of neighbors
        //by the handshaking lemma, oddn has even size
        for(unsigned int u=0;u<mt.g.size();u++){
            if(mt.g[u].size() % 2 != 0){
                oddn.push_back(u);
            }
        }
        
        if(opmat == BLOSSOM_MAT_ALG)
            return blossom_matching(oddn, mt, g);        
        else
            return greedy_matching(oddn, mt, g);
    }    
    
    TSPSolution extract_eulerian_tour(MST& meuler, const ChrisGraph& g){
        TSPSolution sol;
        sol.cost = 0;
        
        stack<unsigned int> av; //active vertices: those that have unused edges
        unsigned int u=0;
        av.push(u); 
        
        while(av.size() > 0){ //while there are vertices with unused edges
            if(meuler.g[u].size() == 0){
                sol.perm.push_back(u);
                u = av.top();
                av.pop();            
            }else{
                av.push(u);    
                unsigned int v = meuler.g[u].front();            
                meuler.g[u].pop_front();

                for(std::list<unsigned int>::iterator ni = meuler.g[v].begin(); ni != meuler.g[v].end(); ni++){ //for each connected edge of this vertex    
                    if(*ni == u){
                        meuler.g[v].erase(ni);
                        break;
                    }
                }
                u=v;   
            }           
        }
        
        return sol;        
    }
    

    
    TSPSolution extract_hamiltonian_tour(TSPSolution sol, const ChrisGraph& g){
        vector<bool> visited(g.dim, false);
        
        sol.cost = 0;
        unsigned int u = sol.perm[0];
        unsigned int i = 0;
        while(i < sol.perm.size() /*sol.perm.size() != g.dim+1*/){ //while the permutation has repeated nodes
            if(not visited[u]){
                unsigned int prev = i == 0 ? 0 : i-1;
                //printf("d[%u,%u] = %u\n", sol.perm[prev], u, g.dist(sol.perm[prev], u));
                sol.cost += g.dist(sol.perm[prev], u);
                visited[u] = true;
                i++;
                u = sol.perm[i];
            }else{
                sol.perm.erase(sol.perm.begin()+i);
                if(i < sol.perm.size());
                    u = sol.perm[i];
            }
        }
        
        u = sol.perm[sol.perm.size()-1];
        sol.cost += g.dist(u, sol.perm[0]);
        
        return sol;
    }
    
//    void check_solution(TSPSolution sol, const ChrisGraph& g){
//        Distance cost = 0;
//        for(unsigned int i=0;i<sol.perm.size();i++){
//            unsigned int j = i+1;
//            if(sol.perm.size() == j)
//                j = 0;
//                
//            cost += g.dist(sol.perm[i],sol.perm[j]);    
//        }
//        
//        //cout << "Checked Dist: " << cost << endl << "Calc. Dist: " << sol.cost << endl;        
//        if(cost != sol.cost){
//            cout << "Error by : " << cost << " != " << sol.cost << endl;
//            exit(-1);
//        }
//    }
    
//    void printTSPSolution(const TSPSolution& sol){
//        cout << "Tour ( " << sol.perm.size() << " ):  " << sol.perm[0];
//        for(unsigned i = 1;i<sol.perm.size();i++){
//            cout << " , " << sol.perm[i];
//        }
//        cout << endl;
//    }
    
//    void prin_mst(MST mt, const char* fname){
//        gv_init(fname);
//        
//        for(unsigned i=0;i<mt.g.size();i++){
//            gv_declare(i);
//        }
//        
//        for(unsigned i=0;i<mt.g.size();i++){
//            for(std::list<unsigned int>::const_iterator it = mt.g[i].begin(); it != mt.g[i].end(); it++){
//                if(mt.edges[*it].used) continue;
//                unsigned int v = mt.edges[*it].v1 == i ? mt.edges[*it].v2 : mt.edges[*it].v1;
//                gv_connect(i, v ,(unsigned)1);
//                mt.edges[*it].used = true;
//            }
//        }
//        
//        gv_close();
//    }
    
    //runs christofides algorithm to get an approximation of a TSP solution
    Distance run_christofides(const ChrisGraph& g, int opmat){
     //   cout << "Searching MST..." << endl;
        MST mt = find_mst(g);
        
       // cout << "Finding match..." << endl;
        MST meuler = find_eulerian_graph(mt, g, opmat);
        
      //  prin_mst(meuler, "mst.dot");
       // cout << "Finding euler tour..." << endl;        
        TSPSolution sol = extract_eulerian_tour(meuler, g);
        
       //cout << "Finding hamiltonian tour..." << endl;
        sol = extract_hamiltonian_tour(sol, g);
       
      //  printTSPSolution(sol); 
      //  check_solution(sol, g);
        
        return sol.cost;
    }
  
    
}
