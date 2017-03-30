#ifndef __NHEAP_H__
#define __NHEAP_H__
#include <vector>
#include <map>

class NHeap{
private:
	std::vector<int> heap; //heap itself, ordering the keys
	std::vector<int> data; //auxilary vector containing the data of each key
	std::map<int, int> pos_heap; //a map to point where in the heap each item is 	
	int n; //heap dimension : n-heap

	//Sifts an item e up, when necessary
	void heapify_up(int key);
	//Sifts an item e down, when necessary
	void heapify_down(int key);
	//Return the parent of node i
	int parent(int i);
	//Return first child of node i
	int first_child(int i);

public:
	//Create a new n-heap with an unique item (key, e)
	NHeap(int n, int key, int e);
	//Insert a new item in the heap (key, e)
	void insert(int key, int e);
	//Update the key of an item e
	void update_key(int nkey, int e);
	//Removes the top-most element, i.e., the minimum
	void deletemin();
	//Return the minimum element
	int getmin();
	void print();

};

#endif //__NHEAP_H__
