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
#include "heap.h"


class NHeap: public Heap{
public:
	
	//Create a new n-heap to support up to m-int-elements with values [0...m-1]
	NHeap(unsigned int m, unsigned int n=2, bool is_min_t=true) : Heap(is_min_t){
	    this->heap.reserve(m);
	    this->data.reserve(m);
	    this->pos_heap.assign(m, 0);
	    this->n = n;
	    this->n_swaps = 0;
    };
    
	//Insert a new item in the heap (key, e)
	void insert(unsigned int e, unsigned int key){
		heap.push_back(key);
	    data.push_back(e);
	    pos_heap[e] = heap.size()-1;	
	    heapify_up(heap.size()-1);
	};
	
	//Update the key of an item e
	void update_key(unsigned int e, unsigned int nkey){
	    unsigned int i = pos_heap[e];
	    unsigned int okey = heap[i]; //old key
	    heap[i] = nkey;
	
	    if(compare(nkey,okey)){ //new key is smaller than previous
	    	heapify_up(i);
	    }else if (compare(okey,nkey)){ //new key is bigger than previous: check if respects propoperties w.r.t. children
	    	heapify_down(i);
	    }
	};
	
	//Removes the top-most element, i.e., the minimum
	void deletetop(){
		if(heap.size() >= 1){
		    heap[0] = heap.back();
		    data[0] = data.back();
		    heap.pop_back();
		    data.pop_back();
		
		    if(heap.size() > 1){
			    pos_heap[data[0]] = 0;
			    heapify_down(0);
		    }
	    }
	};
	
	//true if heap is empty
	bool is_empty(){
	    return (heap.size() == 0);
	};
	
	//Return the minimum element
	unsigned int gettop(){
    	return data[0];
	};
	
	//Return the key of the minimum element
	unsigned int gettopKey(){
	    return heap[0];
	};
	
	unsigned int getsize(){
	    return this->heap.size();
	};
	
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
	void heapify_up(unsigned int i){
		if(i == 0)
		    return;
	
	    unsigned int pi = (i-1)/n; //parent of i 
	    unsigned int hpi = heap[pi];
	    unsigned int hi = heap[i];

	    if(compare(hi,hpi)){ //key is smaller than parent's
		    n_swaps++;
		
		    //swap key
		    heap[i] = hpi;
		    heap[pi] = hi;
		
		    //swap data
		    unsigned int dpi = data[pi];
		    unsigned int di = data[i];
		    data[i] = dpi;
		    data[pi] = di;
		
		    //swap position pointer
		    pos_heap[di] = pi;
		    pos_heap[dpi] = i;

		    heapify_up(pi);
	    }
	};
	
	//Sifts an item e down, when necessary
	void heapify_down(unsigned int i){
		unsigned int min = i;
	
	    unsigned first_child = n*i+1;	//first child of i
	    //get smallest child
	    for(unsigned int j=first_child; j < heap.size() && j-first_child < n;j++){
		    if(compare(heap[j], heap[min]))
			    min = j;
	    }
	    if(min == i) //e is not smaller than any of its children
		    return;	

	    n_swaps++;
		
	    //swap key
	    unsigned int temp = heap[min];
	    heap[min] = heap[i];
	    heap[i] = temp;
	
	    //swap data
	    unsigned int dmin = data[min];
	    temp = data[i];
	    data[i] = data[min];
	    data[min] = temp;
	
	    //swap position pointer
	    pos_heap[temp] = min;
	    pos_heap[dmin] = i;
	
	    heapify_down(min);
	};

};

#endif //__NARY_HEAP_H__
