#include "nheap.h"
#include <math.h>
#include <cstdio>

using namespace std;


NHeap::NHeap(int n, int key, int e){
	this->heap.push_back(key);
	this->data.push_back(e);
	this->pos_heap[e] = 0;
	this->n = n;
}

void NHeap::insert(int key, int e){
	heap.push_back(key);
	data.push_back(e);
	pos_heap[e] = heap.size()-1;
	heapify_up(e);
	printf("added %i, %i at %i\n", key, e, pos_heap[e]);
}

void NHeap::update(int nkey, int e){
	int i = pos_heap[e];
	this->heap[i] = nkey;
	if(heap[i] < heap[parent(i)]){ //key is smaller than parent's
		heapify_up(e);
	}else{
		heapify_down(e);
	}
}

void NHeap::heapify_up(int e){
	int i = pos_heap[e];
	if(i == 0)
		return;
	if(heap[i] < heap[parent(i)]){
		printf("Sensing %i up\n", data[i]);
		//swap key
		int temp = heap[i];
		heap[i] = heap[parent(i)];
		heap[parent(i)] = temp;
		//swap data
		temp = data[i];
		data[i] = data[parent(i)];
		data[parent(i)] = temp;
		
		pos_heap[data[i]] = parent(i);
		pos_heap[data[parent(i)]] = i;
		
		heapify_up(data[parent(i)]);
	}
}

void NHeap::heapify_down(int e){
	int i = pos_heap[e];
	int min = i;
	//get smallest child
	for(int j=first_child(i);j<heap.size();j++){
		if(heap[min] > heap[j])
			min = j;
	}
	
	if(min == i)
		return;	
	
	//swap key
	int temp = heap[min];
	heap[min] = heap[i];
	heap[i] = temp;
	//swap data
	temp = data[min];
	data[min] = data[i];
	data[i] = temp;
	
	pos_heap[data[min]] = i;
	pos_heap[data[i]] = min;
	
	heapify_down(data[min]);
}	

int NHeap::getmin(){
	return data[0];
}

void NHeap::deletemin(){
	if(heap.size() > 1){
		pos_heap.erase(data[0]);
		heap[0] = heap.back();
		data[0] = data.back();
		pos_heap[data[0]] = 0;
	}else if(heap.size() == 1){
		pos_heap.erase(data[0]);
		heap.pop_back();
		data.pop_back();
	}
}

int NHeap::parent(int i){
	return floor((i-1)/n);
}

int NHeap::first_child(int i){
	return n*i+1;
}

