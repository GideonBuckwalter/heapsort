#ifndef HEAPSORT
#define HEAPSORT

// Define a type alias for a key function.
// Takes an object of type T and returns a double.
template <class T>
typedef std::function<double (T)> KeyFunc

// User-friendly heapsort function.
template <class T>
void heapsort(T arr[], int size, KeyFunc key)
{
	heapify(arr, size, key);
	extract_all(arr, size, key);
}

template <class T>
void heapify(T arr[], int size, KeyFunc key)
{

}

template <class T>
void extract_all(T heap[], int size, KeyFunc key)
{

}


#endif // HEAPSORT