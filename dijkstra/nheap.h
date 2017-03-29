
#include <vector>


class NHeap{
private:
	std::vector<int> heap;
	std::vector<int> data;
	std::map<int, int> pos_heap;  	
	int n;

	void heapify_up(int key);
	void heapify_down(int key);

public:
	NHeap(int n, int key, int e);
	void insert(int key, int e);
	void update(int key, ne);
	void deletemin();

};
