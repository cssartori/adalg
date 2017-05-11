#ifndef __HEAP_H__
#define __HEAP_H__

/**
 * Definition of a generic Data Structure Heap Interface.
 *
 * Carlo S. Sartori - 2017/1
 * CMP588 - Advanced Algorithms, UFRGS, Prof. Marcus Ritt
 */

class Heap{

protected:
    //indicates wheter this heap is a min-heap or max-heap
    bool is_min_t;
    
    Heap(bool is_min_t){ 
        this->is_min_t = is_min_t; 
    };
    
    bool compare(unsigned int t1, unsigned int t2){
        if(is_min_t)
            return t1 < t2;
        else
            return t1 > t2;
    };
    
public:
    const static bool MINHEAP = true;
    const static bool MAXHEAP = false;
    
    //variable to hold the number of swaps executed by the heap
	unsigned int n_swaps;

	//Insert a new item in the heap (e, key)
	virtual void insert(unsigned int e, unsigned int key) = 0;
	//Update the key of an item e
	virtual void update_key(unsigned int e, unsigned int nkey) = 0;
	//Removes the top-most element, i.e., the minimum
	virtual void deletetop() = 0;
	//true if heap is empty
	virtual bool is_empty() = 0;
	//Return the minimum element
	virtual unsigned int gettop() = 0;
	//Return the key of the minimum element
	virtual unsigned int gettopKey() = 0;
	//Returns the total number of elements in the heap
	virtual unsigned int getsize() = 0;
	//Destructor
	virtual ~Heap(){};
	//Returns true if heap is min-heap, and false if is a max-heap
	bool is_min(){
	    return this->is_min_t;
	};
    
};

#endif //__HEAP_H__
