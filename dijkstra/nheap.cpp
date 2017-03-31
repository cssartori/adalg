#include "nheap.h"
#include <math.h>
#include <cstdio>

using namespace std;

//Create a new n-heap with an unique item (key, e)
NHeap::NHeap(int n, int key, int e){
	this->heap.push_back(key);
	this->data.push_back(e);
	this->pos_heap[e] = 0;
	this->n = n;
}

//Insert a new item in the heap (key, e)
void NHeap::insert(int key, int e){
	heap.push_back(key);
	data.push_back(e);
	pos_heap[e] = heap.size()-1;
	heapify_up(e);
}

//Update the key of an item e
void NHeap::update_key(int nkey, int e){
	int i = pos_heap[e];
	heap[i] = nkey;
	if(heap[i] < heap[parent(i)]){ //key is smaller than parent's
		heapify_up(e);
	}else{ //check if respects propoperties w.r.t. children
		heapify_down(e);
	}
}

//Sifts an item e up, when necessary
void NHeap::heapify_up(int e){
	int i = pos_heap[e];
	if(i == 0)
		return;
	
	if(heap[i] < heap[parent(i)]){ //key is smaller than parent's
		//swap key
		int temp = heap[i];
		heap[i] = heap[parent(i)];
		heap[parent(i)] = temp;
		
		//swap data
		int dpar = data[parent(i)];
		temp = data[i];
		data[i] = data[parent(i)];
		data[parent(i)] = temp;
		
		//swap position pointer
		pos_heap[e] = parent(i);
		pos_heap[dpar] = i;

		heapify_up(data[parent(i)]);
	}
}

//Sifts an item e down, when necessary
void NHeap::heapify_down(int e){
	int i = pos_heap[e];
	int min = i;
	
	//get smallest child
	for(int j=first_child(i);j<heap.size();j++){
		if(heap[min] > heap[j])
			min = j;
	}
	if(min == i) //e is not smaller than any of its children
		return;	
	
	//swap key
	int temp = heap[min];
	heap[min] = heap[i];
	heap[i] = temp;
	
	//swap data
	int dmin = data[min];
	temp = data[min];
	data[min] = data[i];
	data[i] = temp;
	
	//swap position pointer
	pos_heap[e] = min;
	pos_heap[dmin] = i;
	
	heapify_down(data[min]);
}	

//Return the minimum element
int NHeap::getmin(){
	return data[0];
}

//Removes the top-most element, i.e., the minimum
void NHeap::deletemin(){
	if(heap.size() >= 1){
		pos_heap.erase(data[0]);
		heap[0] = heap.back();
		data[0] = data.back();
		heap.pop_back();
		data.pop_back();
		
		if(heap.size() > 1){
			pos_heap[data[0]] = 0;
			heapify_down(data[0]);
		}
	}
}

//true if heap is empty
bool NHeap::is_empty(){
	return (heap.size() == 0);
}

//Return the parent of node i
int NHeap::parent(int i){
	return floor((i-1)/n);
}

//Return first child of node i
int NHeap::first_child(int i){
	return n*i+1;
}


void NHeap::print(){

	for(int i=0;i<heap.size();i++){
		printf("%i - %i\n",i, heap[i]);
	}

}
