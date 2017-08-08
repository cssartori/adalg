#ifndef __HUNION_FIND_H__
#define __HUNION_FIND_H__

#inclulde <vector>

class UnionFind{
private:
	std::vector<size_t> id; //identification of each set
	std::vector<size_t> tsize; //size of each tree
	
	bool root(size_t i){
		while(id[i] != i){ //follow upward to root node
			id[i] = id[id[i]]; //path compression
			i = id[i];
		}
		return i;
	};
	
public:
	UnionFind(size_t N){
		id.assign(N, 0);
		tsize.assign(N,0);
		for(size_t i=0;i<N;i++) id[i] = i;
	};

	bool find(size_t i, size_t j){
		return root(i) == root(j);
	};

	//wheighted union
	void unite(size_t i, size_t j){
		size_t ri = root(i);
		size_t rj = root(j);
		//merge smaller tree into larger trees to keep them flat
		if(tsize[ri] < tsize[rj]){
			id[ri] = rj;
			tsize[rj] += tsize[ri];
		}else{
			id[rj] = ri;
			tsize[ri] += tsize[rj];
		}
	}
};

#endif //__HUNION_FIND_H__
