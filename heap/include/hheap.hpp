#ifndef __HOLLOW_HEAP_H__
#define __HOLLOW_HEAP_H__

#include <map>
#include <vector>
#include <math.h>
#include "heap.h"

class HHeap: public Heap{
public:
    unsigned int n_links = 0; //link counter
        
    HHeap(unsigned int sz):
        Heap(){
        this->h = make_heap();
        this->ne = 0;
        this->nt = 0;
        this->n_links = 0;
        this->pos_h.reserve(sz);
    };
        
    //inserts a new node (data,key) in the heap
    void insert(unsigned int data, unsigned int key){
        unsigned int *d = new unsigned int;
        *d = data;
        Node *n = make_heap(d, key);
        this->h = meld(this->h, n);
        this->pos_h[data] = n->item;
        
        //A new node has been added to the heap
        this->ne += 1;
        this->nt += 1;
    };
    
    //returns the minimum element
    unsigned int getmin(){        
        return *this->h->item->data;
    };
    
    //decreases the key of a given element of the heap, based on its data
    void decrease_key(unsigned int data, unsigned int key){
        Item *e = this->pos_h[data];

        if(e != nullptr){
            Node *u = e->node;
            Node *v = make_heap(e->data, key);
            v->rank = std::max(0, u->rank-2);
            if(u->rank >= 2){
                v->fc = u->fc->ns->ns;
                u->fc->ns->ns = nullptr;
            }           
            //make u a hollow node
            destroy(u->item);
            u->item = nullptr;
            //update reference to node of element data
            pos_h[data] = v->item;
            
            this->h = meld(this->h, v);
            
            //a hollow node has been added to the heap
            this->nt += 1;
        }
 
    };
    
    void delete_node(unsigned int *data){
        //TODO: is this function really necessary
        Item *e = this->pos_h[*data];
        e->node->item = nullptr;
        if(e->node == this->h)
            deletemin();
    };
    
    //removes the element with minimum key
    void deletemin(){
        // M is the log_phi(N), where phi is the golden ratio (~1.6180) and N the total number of elements in the heap
        unsigned int M = ceil(log(this->nt)/log(GOLDEN_RATIO));
        this->h = remove_min(this->h, M);
    };  
    
    unsigned int getminKey(){
        return this->h->key;  
    };
    
    //Returns true if heap is empty 
    bool is_empty(){
        return (this->h == nullptr);
    };

    unsigned int getnt(){
        return this->nt;
    };
    
    unsigned int getne(){
        return this->ne;
    };


private:
    const double GOLDEN_RATIO = 1.6180;
    class Node; //pre declaration of class Node

    class Item{
    public:
        Node *node;
        unsigned int *data;   
        
        Item(Node *node, unsigned int *data){
            this->node = node;
            this->data = data;
        }
    };

    class Node{
    public:
        Item *item;
        unsigned int key;
        Node *fc; //first child
        Node *ns; //next sibling
        int rank;
        
        Node(unsigned int *data, unsigned int key, Node *fc, Node *ns, int rank){
            this->item = new Item(this, data);
            this->key = key;
            this->fc = fc;
            this->ns = ns;
            this->rank = rank;
        }  
    };

    Node *h;    //node with minimum key
    unsigned int ne; //number of elements in the heap
    unsigned int nt; //number of total nodes in the heap
    //std::map<unsigned int, Item*> pos_h;  //use map for generic cases - does not keep O(1) for decrease_key
    std::vector<Item*> pos_h;   //vector for specific cases
    
    Node* make_heap(){
        return nullptr;
    };

    Node* make_heap(unsigned int *data, unsigned int key){
        Node *n = new Node(data, key, nullptr, nullptr, 0);
        n->ns = n;
        return n;
    };
    

    //connect two different nodes into a single circular list
    Node* meld(Node *h1, Node *h2){
        if(h1 == nullptr)
            return h2;
        else if(h2 == nullptr)
            return h1;
        
        //swap its next pointers to connect them
        Node *temp = h1->ns;
        h1->ns = h2->ns;
        h2->ns = temp;
        
        //return the one with smallest key
        if(h1->key <= h2->key)
            return h1;
        else
            return h2;
    };
    
    //link two nodes (trees) into a single one   
    Node* link(Node *t1, Node *t2){
        //comparison produces a winner and a loser
        if(t1->key <= t2->key)
            return make_child(t1, t2);
        else
            return make_child(t2, t1);
    };
    
    //given a winner node and a loser, make the loser child of winner and increase rank of winner
    Node* make_child(Node *winner, Node *loser){
        loser->ns = winner->fc;
        winner->fc = loser;
        winner->rank += 1;
        return winner;
    };
    
    //removes the element with minimum key
    Node* remove_min(Node *hr, unsigned int M){
        if(hr == nullptr || hr->item == nullptr)
            return nullptr;
        
        //makes hr hollow node
        destroy(hr->item, true);
        hr->item = nullptr;
        //removed a normal node
        this->ne -= 1;
        
        //vector of references to nodes of the heap
        std::vector<Node*> R(M, nullptr);
        Node *r = hr;
        //loop to recover the references to each root
        do{
            Node *rn = r->ns;            
            link_heap(r, &R);
            r = rn;
        }while(r != hr && r != nullptr);

        //Rebuild heap from "scratch"              
        hr = nullptr; 
        for(unsigned i=0;i<M;i++){
            if(R[i] != nullptr){
                R[i]->ns = R[i]; //connect node to itself
                hr = meld(hr, R[i]); //meld node to the resto of the heap
            }            
        }
        return hr;
    };
    
    
    //link heap removing hollow nodes
    void link_heap(Node *hr, std::vector<Node*> *R){
        
        this->n_links += 1; //executed one link_heap, that is, one "swap"
        if(hr->item == nullptr){
            //node hr is hollow
            Node *r = hr->fc;
            while(r != nullptr){ //go through the list of childs of h
                Node *rn = r->ns;
                link_heap(r, R); //link each child to remove hollows
                r = rn;
            }
            
            destroy(hr);
            hr = nullptr;
            //removed a hollow node
            this->nt -= 1;
        }else{
            unsigned int i = hr->rank;
            //go over each reference in R
            while((*R)[i] != nullptr){
                hr = link(hr, (*R)[i]); //link the reference to the node hr
                (*R)[i] = nullptr;
                i++;
            }
            (*R)[i] = hr;
        }
    };
        
    void destroy(Item *e, bool a = false){
        if(e != nullptr){
            if(a){
                //pos_h.erase(*e->data);
                pos_h[*e->data] = nullptr;
                delete e->data;
            }
            
            delete e;
        }
    }
    
    void destroy(Node *n, bool a = false){
        if(n != nullptr){
            destroy(n->item, a);
            delete n;
        }
    }
};

#endif //__HOLLOW_HEAP_H__
