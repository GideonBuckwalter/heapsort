#ifndef HEAPSORT
#define HEAPSORT

#include <functional>
#include <assert.h>

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

	void swap(T* a, T* b)
	{
		T temp = *a;
		*a = *b;
		*b = temp;
	}

	T* max(T* a, T* b, T* c)
	{
		if (key(*a) > key(*b) && key(*a) > key(*c))
			return a;
		if (key(*b) > key(*a) && key(*b) > key(*c))
			return b;
		return c;
	}


public:
	// Main heapsort function: constructor.
	HeapSort(T array[], int size, std::function<double (T)> key)
	{
		this->head = array
		this->size = size;
		this->key = key;
	}

	// If you don't specify a key function, a default will be used.
	HeapSort(T array[], int size)
	{
		this->head = array;
		this->size = size;
		this->key = [] (T value) { return static_cast<double>(value); };
	}

	// Use this function to actually perform the heapsort.
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

	void percolateUp(T* end)
	{
		// Base case.
		if (!hasParent(end))
			return;

		if (key(*end) > key(*parent(end)))
		{
			swap(end, parent(end));
			percolateUp(parent(end));
		}
	}

	void percolateDown(T* start)
	{
		// Base case.
		if (isLeaf(start))
			return;

		if (hasChildR(start)) // Has two children
		{
			T* m = max(start, childL(start), childR(start));
			if (key(*m) != key(*start))
			{
				swap(start, m);
				percolateDown(m);
			}
		}
		else // Node has only a left child.
		{
			if (key(*start) < key(*childL(start)))
				swap(start, childL(start));
		}
	}

	friend void testHeapSort();
};


void testHeapSort()
{
	int arr[10] = {4,2,1,5,7,9,3,8,0,6};
	HeapSort<int> hs(arr, 10); // Uses default key function.
}


#endif // HEAPSORT