#ifndef HEAPSORT
#define HEAPSORT

#include <functional>



// HELPER FUNCTIONS //

int parent(int i) { return (i + 1)/2; }
int childL(int i) { return (i + 1)*2; }
int childR(int i) { return (i + 1)*2 + 1; }

bool hasChildL(int i, int size) { return childL(i) < size; }
bool hasChildR(int i, int size) { return childR(i) < size; }

bool isLeaf(int i, int size)
{ return !hasChildL(i, size) && !hasChildR(i, size); } // Simplification?



// MAIN FUNCTIONS //

// Main heapsort function.
template <class T>
void heapsort(T arr[], int size, std::function<double (T)> key)
{
	heapify(arr, size, key);
	extractAll(arr, size, key);
}

template <class T>
void heapify(T arr[], int size, std::function<double (T)> key)
{

}

template <class T>
void extractAll(T heap[], int size, std::function<double (T)> key)
{

}


#endif // HEAPSORT