#ifndef BINHEAP_HPP
#define BINHEAP_HPP

#include <iostream>
#include <cstdlib>
#include <exception>
#include <functional>

/*
class HeapException : public exception
{
public:
	HeapException(void);
	const char *what(void);
private:
	static char *errormsg;
};

class HeapOverflowException : public HeapException {};
class HeapUndeflowException : public HeapException {};

HeapException::HeapException(void) : errormsg(NULL) {}
HeapException::what(void){return errormsg;}

HeapOverflowException::HeapOverflowException 
: errormsg("Heap Overflow Exception.") {}

HeapUnderflowException::HeapOverflowException
: errormsg("Heap Underflow Exception.") {}
*/

template <class T, class Compare=std::less<T> >
class BinHeap
{
public:
	BinHeap(const Compare &comp);
	~BinHeap(void);
	void insert(T item);
	T remove(void);
	T top(void);
	int getSize(void);

private:
	T *heap;
	int capacity;
	int size;
	Compare comp;
};

template <class T, class Compare>
BinHeap<T, Compare>::BinHeap(const Compare& comp = Compare())
	:capacity(1), size(1), comp(comp)
{
	heap = new T[capacity];
}

template <class T, class Compare>
BinHeap<T, Compare>::~BinHeap(void)
{
	delete heap;
}

template <class T>
void heap_swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <class T, class Compare>
void BinHeap<T, Compare>::insert(T item)
{
	if (size == capacity) {
		T *newPtr;
		newPtr = (T*) realloc(heap, capacity*2 * sizeof(T));
		if (newPtr == NULL) {
			//throw HeapOverflowException;
			return;
		} 
		heap = newPtr;
		capacity *= 2;
	}
	heap[size] = item;
	int i = size;
	while (comp(heap[i], heap[i/2])) {
		heap_swap(heap[i], heap[i/2]);
		i /= 2;
	}
	size++;
}

template <class T, class Compare>
T BinHeap<T, Compare>::remove(void)
{
	if (size == 1) {
		throw (std::exception());
	}
	size--;
	heap_swap(heap[1], heap[size]);
	T out = heap[size];
	if (size <= capacity/4) {
		capacity /= 2;
		heap = (T*) realloc(heap, capacity * sizeof(T));
	}

	int i = 1;
	int next;

	// Bubble the top back into place.
	while (i) {
		if (2*i < size) {
			if (2*i + 1 < size) {
				next = comp(heap[2*i], heap[2*i + 1]) ?
					2*i : 2*i + 1;
			} else {
				next = 2*i;
			}
		} else {
			break;
		}

		if (comp(heap[next], heap[i])) {
			heap_swap(heap[next], heap[i]);
			i = next;
		} else {
			break;
		}
	}

	return out;
}

template <class T, class Compare>
T BinHeap<T, Compare>::top(void)
{
	if (size <= 1) {
		throw (std::exception());
	}
	return heap[1];
}

template <class T, class Compare>
int BinHeap<T, Compare>::getSize(void)
{
	return size - 1;
}

#endif
