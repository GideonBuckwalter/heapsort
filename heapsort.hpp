#ifndef HEAPSORT
#define HEAPSORT

#include <functional>


template <class T>
class HeapSort
{
private:
	T* head;
	int size;
	std::function<double (T)> key;

	// HELPER FUNCTIONS //

	// Returns the index of the given pointer relative to 'head'.
	// If ptr == head, return 0
	int index(T* ptr) { return static_cast<int>(ptr - head); }

	// Return pointers to parents and children of given pointers.
	T* parent(T* ptr) { return head + (index(ptr) - 1)/2; }
	T* childL(T* ptr) { return head + index(ptr)*2 + 1; }
	T* childR(T* ptr) { return head + index(ptr)*2 + 2; }

	// Check for existence of children/parents of a given pointer.
	bool hasParent(T* ptr) { return parent(ptr) > head; }
	bool hasChildL(T* ptr) { return childL(ptr) <= head + size; }
	bool hasChildR(T* ptr) { return childR(ptr) <= head + size; }

	// Tests if a given pointer points to a leaf node.
	// NOTE: If node had no left node, it cannot have a right node either.
	bool isLeaf(T* ptr)
	{ return !hasChildL(ptr); }



	// MAIN FUNCTIONS //

	// Main heapsort function.
	HeapSort(T array[], int size, std::function<double (T)> key)
	{
		this->head = array
		this->size = size;
		this->key = key;
	}

	void go()
	{
		heapify();
		extractAll();
	}

	void heapify()
	{

	}

	void extractAll()
	{

	}

	void percolateDown(T* start, T* end)
	{

	}
};


#endif // HEAPSORT