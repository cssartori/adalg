#ifndef __NHEAP_H__
#define __NHEAP_H__
#include <vector>
#include <map>


template <class HT>
class NHeap{
private:
	std::vector<HT> heap; //heap itself, ordering the keys
	std::map<HT, unsigned int> pos_heap; //a map to point where in the heap each item is 	
	unsigned int n; //heap dimension : n-heap

	//Sifts an item e up, when necessary
	void heapify_up(unsigned int i){
		if(i == 0)
			return;
	
		if(heap[i] < heap[parent(i)]){ //key is smaller than parent's
			n_swaps++;
		
			//swap key
			HT temp = heap[i];
			heap[i] = heap[parent(i)];
			heap[parent(i)] = temp;
			
			//swap position pointer
			pos_heap[temp] = parent(i);
			pos_heap[heap[i]] = i;

			heapify_up(parent(i));
		}
	};
	
	//Sifts an item e down, when necessary
	void heapify_down(unsigned int i){
		unsigned int min = i;
	
		//get smallest child
		for(unsigned int j=first_child(i); j<heap.size() ;j++){
			if(heap[j] < heap[min])
				min = j;
		}
		if(min == i) //e is not smaller than any of its children
			return;	
	
		n_swaps++;
	
		//swap key
		HT temp = heap[min];
		heap[min] = heap[i];
		heap[i] = temp;
	
		//swap position pointer
		pos_heap[temp] = i;
		pos_heap[heap[min]] = min;
	
		heapify_down(min);
	};
	
	//Return the parent of node i
	unsigned int parent(unsigned int i){
		return (i-1)/n;
	};
	
	//Return first child of node i
	unsigned int first_child(unsigned int i){
		return n*i+1;
	};

public:
	unsigned int n_swaps;
	
	
	
	//Create a new n-heap with an unique item (key, e)
	NHeap(unsigned int n, unsigned int m=32){
		//this->heap.reserve(m);
		this->n = n;
	};
	
	//Insert a new item in the heap (key, e)
	void insert(HT e){
		heap.push_back(e);
		pos_heap[e] = heap.size()-1;
		heapify_up(heap.size()-1);
	};
	
	//Update the key of an item e
	void update_key(HT e, HT ne){
		unsigned int i = pos_heap[e];
		heap[i] = ne;
		if(ne < e){ 		//new key is smaller than previous
			heapify_up(i);
		}else{ 				//new key is bigger than previous: check if respects propoperties w.r.t. children
			heapify_down(i);
		}
	};
	
	//Removes the top-most element, i.e., the minimum
	void deletemin(){
		if(heap.size() >= 1){
			pos_heap.erase(heap[0]);
			heap[0] = heap.back();
			heap.pop_back();
			
			if(heap.size() > 1){
				pos_heap[heap[0]] = 0;
				heapify_down(0);
			}
		}
	};
	
	//true if heap is empty
	bool is_empty(){
		return (heap.size() == 0);
	};
	
	//Return the minimum element
	HT getmin(){
		return heap[0];
	};
};

#endif //__NHEAP_H__
