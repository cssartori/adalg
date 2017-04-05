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
	
	if(heap[i] < heap[parent(i)]){ //key is smaller than parent's
		n_swaps++;
		
		//swap key
		unsigned int temp = heap[i];
		heap[i] = heap[parent(i)];
		heap[parent(i)] = temp;
		
		//swap data
		unsigned int dpar = data[parent(i)];
		temp = data[i];
		data[i] = data[parent(i)];
		data[parent(i)] = temp;
		
		//swap position pointer
		pos_heap[temp] = parent(i);
		pos_heap[dpar] = i;

		heapify_up(parent(i));
	}
}

//Sifts an item e down, when necessary
void NHeap::heapify_down(unsigned int i){
	unsigned int min = i;
	
	//get smallest child
	for(unsigned int j=first_child(i); j<heap.size() && j-first_child(i) < n;j++){
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

//Return the parent of node i
unsigned int NHeap::parent(unsigned int i){
	return (i-1)/n;
}

//Return first child of node i
unsigned int NHeap::first_child(unsigned int i){
	return n*i+1;
}


void NHeap::print(){

	for(int i=0;i<heap.size();i++){
		printf("%i - %i\n",i, heap[i]);
	}

}
