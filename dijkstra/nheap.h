
#include <vector>
#include <map>

class NHeap{
private:
	std::vector<int> heap;
	std::vector<int> data;
	std::map<int, int> pos_heap;  	
	int n;

	void heapify_up(int key);
	void heapify_down(int key);
	int parent(int i);
	int first_child(int i);

public:
	NHeap(int n, int key, int e);
	void insert(int key, int e);
	void update(int nkey, int e);
	void deletemin();
	int getmin();

};
