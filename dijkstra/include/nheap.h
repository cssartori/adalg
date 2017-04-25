#ifndef __NARY_HEAP_H__
#define __NARY_HEAP_H__

/**
 * Implementation of a n-heap data structure, where n is the maximum number of 
 * children each node my have. It is specially suited to work with integer input
 * values, such as Graph's node index and distances for Dijkstra's algorithm.
 *
 * Carlo S. Sartori - 2017/1
 * CMP588 - Advanced Algorithms, UFRGS, Prof. Marcus Ritt
 */

#include <vector>


class NHeap{
private:
    //heap itself, ordering the keys
	std::vector<unsigned int> heap;
	//auxilary vector containing the satelite data of each key 
	std::vector<unsigned int> data;
	//a map to point where in the heap each item is - more generally a map 
	std::vector<unsigned int> pos_heap; 
	//heap dimension : n-heap
	unsigned int n; 


	//Sifts an item e up, when necessary
	void heapify_up(unsigned int i);
	//Sifts an item e down, when necessary
	void heapify_down(unsigned int i);

public:
    //variable to hold the number of swaps executed by the heap
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

};

#endif //__NARY_HEAP_H__
