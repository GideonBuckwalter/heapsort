#ifndef HEAPSORT
#define HEAPSORT

#include <functional>
#include <iomanip>
#include <assert.h>
#include <cstdlib>	// rand, srand
#include <ctime>	// time

template <class T, class K>
class Heap
{
private:
	T* head;
	int size;
	std::function<double (T)> key;

	// HELPER FUNCTIONS //

	// Returns the index of the given pointer relative to 'head'.
	// If ptr == head, return 0
	int index(T* ptr) { return static_cast<int>(ptr - head); }

	// Returns a pointer to the last array element.
	T* last() { return head + size - 1; }

	// Return pointers to parents and children of given pointers.
	T* parent(T* ptr) { return head + (index(ptr) - 1)/2; }
	T* childL(T* ptr) { return head + index(ptr)*2 + 1; }
	T* childR(T* ptr) { return head + index(ptr)*2 + 2; }

	bool isValidNode(T* ptr) { return ptr < head + size && ptr >= head; }

	// Check for existence of children/parents of a given pointer.
	bool hasParent(T* ptr) { return isValidNode(parent(ptr)); }
	bool hasChildL(T* ptr) { return isValidNode(childL(ptr)); }
	bool hasChildR(T* ptr) { return isValidNode(childR(ptr)); }

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
		if (key(*a) >= key(*b) && key(*a) >= key(*c))
			return a;
		if (key(*b) >= key(*a) && key(*b) >= key(*c))
			return b;
		return c;
	}

	void printNode(T* node, std::ostream& out, int indent)
	{
		// Base case.
		if (!isValidNode(node))
			return;

		// Right-Node-Left traversal, printed sideways.
		printNode(childR(node), out, indent+4);
		out << std::setw(indent) << *node << std::endl;
		printNode(childL(node), out, indent+4);
	}

	bool upholdsHeapOrderProperty(T* subheap)
	{
		if (isLeaf(subheap))
			return true;

		if (!isValidNode(childR(subheap)))
			// We know it's not a leaf, so must have left child.
			return key(*subheap) >= key(*childL(subheap));


		return key(*subheap) >= key(*childL(subheap)) &&
			   key(*subheap) >= key(*childR(subheap)) &&
			   upholdsHeapOrderProperty(childL(subheap)) &&
			   upholdsHeapOrderProperty(childR(subheap));
	}


public:

	static void sort(T array[], int size, std::function<K (T)> key)
	{
		// Create a local instance.
		// User doesn't need to manage this instance.
		Heap heap(array, size, key);
		heap.heapify();
		heap.extractAll();
	}

	static void sort(T array[], int size)
	{
		Heap::sort(array, size, [](T x){ return static_cast<K>(x); });
	}

	// Main heapsort function: constructor.
	Heap(T array[], int size, std::function<K (T)> key)
	{
		this->head = array;
		this->size = size;
		this->key = key;
	}

	// If you don't specify a key function, a default will be used.
	Heap(T array[], int size)
	{
		this->head = array;
		this->size = size;
		this->key = [] (T value) { return static_cast<K>(value); };
	}

	// Use this function to actually perform the heapsort.
	void go()
	{
		heapify();
		extractAll();
	}

	void heapify()
	{
		for (T* ptr = parent(last()); isValidNode(ptr); ptr--)
			percolateDown(ptr);
	}

	void extractAll()
	{
		int SIZE = size; // Save the original size.
		for (int i = 0; i < SIZE-1; i++)
		{
			swap(head, last());
			size--; // Make heap think size has changed.
			percolateDown(head);
		}

		// Make heap remember what the ACTUAL size is.
		size = SIZE;
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
			T* big = max(start, childL(start), childR(start));
			if (key(*big) != key(*start))
			{
				swap(start, big);
				percolateDown(big);
			}
		}
		else // Node has only a left child.
		{
			if (key(*start) < key(*childL(start)))
				swap(start, childL(start));
		}
	}

	void print(std::ostream& out)
	{
		printNode(head, out, 0);
	}

	bool isSorted()
	{
		for (int i = 1; i < size; i++)
			if (key(head[i - 1]) > key(head[i]))
			{
				std::cout << "Not ascending!" << std::endl;
				std::cout << "\thead[" << i-1 << "]=" << head[i-1] << std::endl;
				std::cout << "\thead[" << i   << "]=" << head[i]   << std::endl;
				return false;
			}
		return true;
	}

	bool upholdsHeapOrderProperty()
	{
		return upholdsHeapOrderProperty(head);
	}

	friend void testHeapSort();
};


void testHeapSort()
{
	{
		int arr[10] = {4,2,1,5,7,9,3,8,0,6};
		Heap<int, int> hs(arr, 10); // Uses default key function.

		std::cout << "Initial Array:" << std::endl;
		for (int x : arr)
			std::cout << x << " ";
		std::cout << std::endl;

		std::cout << std::endl;
		std::cout << "Initial Heap:" << std::endl;
		hs.print(std::cout);

		std::cout << std::endl;
		std::cout << "Heapify:" << std::endl;
		hs.heapify();
		assert(hs.upholdsHeapOrderProperty());
		hs.print(std::cout);

		std::cout << std::endl;
		std::cout << "Extract All:" << std::endl;
		hs.extractAll();
		hs.print(std::cout);

		std::cout << std::endl;
		std::cout << "Final Array:" << std::endl;
		for (int x : arr)
			std::cout << x << " ";
		std::cout << std::endl;

		assert(hs.isSorted());
	}

	{
		srand(time(0));

		const int SIZE = 100000;
		int arr[SIZE];

		for (int i = 0; i < SIZE; i++)
			arr[i] = rand() % (1*SIZE);


		Heap<int, int> heap(arr, SIZE);

		// Record time taken.
		std::clock_t t0 = std::clock();
		heap.go();
		std::clock_t dt = (std::clock() - t0) / (double)(CLOCKS_PER_SEC / 1000);

		std::cout << std::endl;
		std::cout << "Time taken to sort " << SIZE << " integers: "
				  << dt << "ms" << std::endl;
		assert(heap.isSorted());
	}

	{
		// Test static sort method.
		const int SIZE = 10;
		int array[SIZE] = {321,53,75,144,769,3134,806,28,584,128};
		Heap<int, int>::sort(array, SIZE, [](int x){ return static_cast<double>(x); });
		for (int i = 1; i < SIZE; i++)
			assert(array[i-1] <= array[i]);
	}

	{
		// Test overloaded static sort method.
		const int SIZE = 10;
		int array[SIZE] = {321,53,75,144,769,3134,806,28,584,128};
		Heap<int, int>::sort(array, SIZE);
		for (int i = 1; i < SIZE; i++)
			assert(array[i-1] <= array[i]);
	}

}


#endif // HEAPSORT