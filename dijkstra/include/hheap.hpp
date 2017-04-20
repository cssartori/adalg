#ifndef __H_HEAP__
#define __H_HEAP__

#include <map>
#include <vector>
#include <math.h>

class HHeap{
public:
    
    HHeap(){
        this->h = make_heap();
        this->ne = 0;
        this->nt = 0;
    };
    
    HHeap(unsigned int *data, unsigned int key){
        this->h = make_heap(data, key);
        this->pos_h[*data] = this->h->item;
        //A new node has been added to the heap
        this->ne = 1;
        this->nt = 1;
    };

    void insert(unsigned int *data, unsigned int key){
        Node *n = make_heap(data, key);
//        if(n == nullptr)
//            printf("Inserting null pointer\n");
//        else
//            printf("n = (%u,%u) | n = %u | ns = %u | fc = %u\n", *n->item->data, n->key, n, n->ns, n->fc);
        this->h = meld(this->h, n);
        this->pos_h[*data] = n->item;
        //A new node has been added to the heap
        this->ne += 1;
        this->nt += 1;
    };
    
    unsigned int* getmin(){
        if(this->h == nullptr || this->h->item == nullptr)
            return nullptr;
        return this->h->item->data;
    };
    
    void update_key(unsigned int *data, unsigned int key){
        Item *e = this->pos_h[*data];
        if(e != nullptr){
            Node *u = e->node;
            Node *v = make_heap(e->data, key);
            v->rank = std::max((unsigned int)0, u->rank-2);
            if(u->rank >= 2){
                v->fc = u->ns->ns;
                u->ns->ns = nullptr;
            }
            u->item = nullptr;
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
            delete_min();
    };
    
    void delete_min(){
        unsigned int M = ceil(log(this->nt)/log(1.6180));
        this->h = remove_min(this->h, M);
    };  

    bool is_empty(){
        return this->h == nullptr;
    }

    unsigned int getnt(){
        return this->nt;
    };
    
    unsigned int getne(){
        return this->ne;
    };

    void print_roots(){
        Node *ht = this->h;

        do{
            printf("%u\n", *(ht->item->data));
            ht = ht->ns;
        }while(ht != this->h)  ;
    };

private:
    class Node;

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
        unsigned int rank;
        
        Node(unsigned int *data, unsigned int key, Node *fc, Node *ns, unsigned int rank){
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
    std::map<unsigned int, Item*> pos_h;  

    Node* make_heap(){
        return nullptr;
    };

    Node* make_heap(unsigned int *data, unsigned int key){
        Node *n = new Node(data, key, nullptr, this->h, (unsigned int)0);
        n->ns = n;
        return n;
    };
    
    Node* meld(Node *h1, Node *h2){
        if(h1 == nullptr)
            return h2;
        else if(h2 == nullptr)
            return h1;

        Node *temp = h1->ns;
       // printf("temp = %u\n", temp);
        h1->ns = h2->ns;
       // printf("-temp = %u\n", temp);
        h2->ns = temp;
        
       // printf ("(%u,%u) - > (%u,%u)\n", *h2->item->data, h2->key, *h2->ns->item->data, h2->ns->key);
        
        if(h1->key <= h2->key)
            return h1;
        else
            return h2;
    };

    Node* link(Node *t1, Node *t2){
        if(t1->key <= t2->key)
            return make_child(t1, t2);
        else
            return make_child(t2, t1);
    };

    Node* make_child(Node *winner, Node *loser){
        loser->ns = winner->fc;
        winner->fc = loser;
        winner->rank += 1;
        return winner;
    };
    
    Node* remove_min(Node *hr, unsigned int M){
        if(hr == nullptr || hr->item == nullptr)
            return nullptr;
        
        hr->item = nullptr;
        //removed a normal node
        this->ne -= 1;
        
        std::vector<Node*> R(M, nullptr);
        Node *r = hr;
      //  printf("Starting link_heap loop\n");
        do{
            Node *rn = r->ns;
            link_heap(r, &R);
            r = rn;
        }while(r != hr);
        
      //  printf("Finished loop\n");
        
        //Rebuild heap              
        hr = nullptr;
      //  printf("Startging last loop\n");
        for(unsigned i=0;i<M;i++){
            if(R[i] != nullptr){
                R[i]->ns = R[i];
                hr = meld(hr, R[i]);
            }            
        }
       // printf("Returning %u\n", hr);
        return hr;
    };
    
    //link heap removing hollow nodes
    void link_heap(Node *hr, std::vector<Node*> *R){
      //  printf("Link_heap\n");
        if(hr->item == nullptr){
            Node *r = hr->fc;
            while(r != nullptr){ //go through the list of childs of h
                Node *rn = r->ns;
                link_heap(r, R); //link each child to remove hollows
                r = rn;
            }
            delete hr;
            //removed a hollow node
            this->nt -= 1;
        }else{
            unsigned int i = hr->rank;
            //go over each reference in R
            while((*R)[i] != nullptr){
                hr = link(hr, (*R)[i]); //link the reference to the heap h
                (*R)[i] = nullptr;
                i++;
            }
            (*R)[i] = hr;
        }         
    };
};

#endif //__H_HEAP__
