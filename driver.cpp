#include <iostream>
#include "heapsort.hpp"
using namespace std;

template <class T>
void printArray(T array[], int size)
{
	cout << "{ ";
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << "}" << endl;
}

int main()
{
	// Run automated tests on Heap class.
	testHeapSort(false);

	// Sort array given in problem statement.
	const int SIZE = 25;
	int array[SIZE] = {72, 85, 9, 307, 25, 506, 182, 175, 10, 64, 430, 399, 2,
			           71, 90, 55, 471, 250, 18, 222, 49, 103, 550, 341, 273};

	cout << endl;
	cout << "Unmodified Array:" << endl;
	printArray(array, SIZE);
	Heap<int, int>::print(array, SIZE, cout);

	cout << endl;
	cout << "Heapified Array:" << endl;
	Heap<int, int>::heapify(array, SIZE);
	printArray(array, SIZE);
	Heap<int, int>::print(array, SIZE, cout);

	cout << endl;
	cout << "Sorted Array:" << endl;
	Heap<int, int>::extract(array, SIZE);
	printArray(array, SIZE);
	Heap<int, int>::print(array, SIZE, cout);

	return 0;
}