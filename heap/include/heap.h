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
    bool is_min;
    
    Heap(bool is_min){ 
        this->is_min = is_min; 
    };
    
    bool compare(unsigned int t1, unsigned int t2){
        if(is_min)
            return t1 < t2;
        else
            return t1 > t2;
    };
    
public:
	//Insert a new item in the heap (e, key)
	virtual void insert(unsigned int e, unsigned int key) = 0;
	//Update the key of an item e
	virtual void update_key(unsigned int e, unsigned int nkey) = 0;
	//Removes the top-most element, i.e., the minimum
	virtual void deletemin() = 0;
	//true if heap is empty
	virtual bool is_empty() = 0;
	//Return the minimum element
	virtual unsigned int getmin() = 0;
	//Return the key of the minimum element
	virtual unsigned int getminKey() = 0;
	
	virtual ~Heap(){};
    
};

#endif //__HEAP_H__
