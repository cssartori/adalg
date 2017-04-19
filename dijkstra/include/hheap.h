#ifndef __H_HEAP__
#define __H_HEAP__

class Item{
    Node *node;
    unsigned int *data;   
    
    Item(Node *node, unsigned int *data){
        this->node = node;
        this->data = data;
    }
};

class Node{
    Item *item;
    unsigned int key;
    Node *fc; //first child
    Node *ns; //next sibling
    unsigned int rank;
    
    Node(unsigned int *data, unsigned int key, Node *fc, Node *ns, unsigned int rank){
        this->item = new Item(this, data);
        this->key = key;
        this->fc = fc;
        this->ns = ns;
        this->rank = rank;
    }  
};

class HHeap{
private:
    Node *h;    //node with minimum key
    unsigned int ne; //number of elements in the heap
    unsigned int nh; //number of hollows in the heap

    Node* make_heap(){
        return nullptr;
    }

    Node* make_heap(unsigned int *data, unsigned int key){
        return new Node(data, key, nullptr, this, 0);
    }
        
public:
    HHeap(){
        this->h = make_heap();
        this->ne = 0;
        this->nh = 0;
    }
    
    HHeap(unsigned int *data, unsigned int key){
        this->h = make_heap(data, key, nullptr, this, 0);
        this->ne = 1;
        this->nh = 0;
    }

}

#endif //__H_HEAP__
