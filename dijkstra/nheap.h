#ifndef __NHEAP_H__
#define __NHEAP_H__
#include <vector>
#include <unordered_map>


//template <class HT>
class NHeap{
private:
	std::vector<int> heap; //heap itself, ordering the keys
	std::vector<int> data; //auxilary vector containing the data of each key
	std::unordered_map<int, unsigned int> pos_heap; //a map to point where in the heap each item is 	
	unsigned int n; //heap dimension : n-heap

	//Sifts an item e up, when necessary
	void heapify_up(unsigned int i);
	//Sifts an item e down, when necessary
	void heapify_down(unsigned int i);
	//Return the parent of node i
	unsigned int parent(unsigned int i);
	//Return first child of node i
	unsigned int first_child(unsigned int i);

public:
	unsigned int n_swaps;
	
	//Create a new n-heap with an unique item (key, e)
	NHeap(unsigned int n, unsigned int m);
	//Insert a new item in the heap (key, e)
	void insert(int key, int e);
	//Update the key of an item e
	void update_key(int nkey, int e);
	//Removes the top-most element, i.e., the minimum
	void deletemin();
	//true if heap is empty
	bool is_empty();
	//Return the minimum element
	int getmin();
	void print();

};

#endif //__NHEAP_H__
