#ifndef __NHEAP_H__
#define __NHEAP_H__
#include <vector>
#include <unordered_map>


class NHeap{
private:
	std::vector<unsigned int> heap; //heap itself, ordering the keys
	std::vector<unsigned int> data; //auxilary vector containing the data of each key
	std::vector<unsigned int> pos_heap; //a map to point where in the heap each item is - could be a map
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
	
	//Create a new n-heap to support up to m-int-elements with values [0...m-1]
	NHeap(unsigned int n, unsigned int m);
	//Insert a new item in the heap (key, e)
	void insert(unsigned int key, unsigned int e);
	//Update the key of an item e
	void update_key(unsigned int e, unsigned int nkey);
	//Removes the top-most element, i.e., the minimum
	void deletemin();
	//true if heap is empty
	bool is_empty();
	//Return the minimum element
	unsigned int getmin();
	//Return the key of the minimum element
	unsigned int getminKey();
	void print();

};

#endif //__NHEAP_H__
