#include "nheap.h"
#include <math.h>
#include <cstdio>

using namespace std;

//Create a new n-heap to support up to m-int-elements with values [0...m-1]
NHeap::NHeap(unsigned int n, unsigned int m){
	this->heap.reserve(m);
	this->data.reserve(m);
	this->pos_heap.assign(m, 0);
	this->n = n;
}

//Insert a new item in the heap (key, e)
void NHeap::insert(unsigned int key, unsigned int e){
	heap.push_back(key);
	data.push_back(e);
	pos_heap[e] = heap.size()-1;
	
	heapify_up(heap.size()-1);
}

//Update the key of an item e
void NHeap::update_key(unsigned int e, unsigned int nkey){
	unsigned int i = pos_heap[e];
	unsigned int okey = heap[i]; //old key
	heap[i] = nkey;
	
	if(nkey < okey){ //new key is smaller than previous
		heapify_up(i);
	}else if (nkey > okey){ //new key is bigger than previous: check if respects propoperties w.r.t. children
		heapify_down(i);
	}
}

//Sifts an item e up, when necessary
void NHeap::heapify_up(unsigned int i){
	if(i == 0)
		return;
	
	unsigned int pi = (i-1)/n; //parent of i 
	unsigned int hpi = heap[pi];
	unsigned int hi = heap[i];
	
	if(hi < hpi){ //key is smaller than parent's
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
}

//Sifts an item e down, when necessary
void NHeap::heapify_down(unsigned int i){
	unsigned int min = i;
	
	unsigned first_child = n*i+1;	//first child of i
	//get smallest child
	for(unsigned int j=first_child; j<heap.size() && j-first_child < n;j++){
		if(heap[j] < heap[min])
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
}	

//Return the minimum element
unsigned int NHeap::getmin(){
	return data[0];
}

//Return the minimum element
unsigned int NHeap::getminKey(){
	return heap[0];
}

//Removes the top-most element, i.e., the minimum
void NHeap::deletemin(){
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
}

//true if heap is empty
bool NHeap::is_empty(){
	return (heap.size() == 0);
}
