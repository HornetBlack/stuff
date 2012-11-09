
#include <iostream>
#include <functional>
#include <utility>
#include "binheap.hpp"

#define TEST_SEED 0x12345678
#define TEST_SIZE 32

using namespace std;

class compare : public binary_function <int, int, bool> 
{
public:
	bool operator()(pair<int, int> a, pair<int, int> b)
		{
			if (a.first != b.first) {
				return a.first < b.first;
			} else {
				return a.second < b.second;
			}
		}
};

int main(int argc, char *argv[])
{
	using namespace std;

	srand(TEST_SEED);

	cout << "Testing standard ints" << endl;
	BinHeap <int, greater<int> > heap;
	cout << "In:" << endl;
	for (int i = 0; i < TEST_SIZE; i++) {
		int r = rand() % TEST_SIZE;
		heap.insert(r);
		cout << r << " ";
	}
	
	cout << endl << "Out:" << endl;
	while (heap.getSize() > 0) {
		cout << heap.remove() << " ";
	}
	cout << endl;


	cout << "Testing cartesian pairs of ints" << endl;
	BinHeap <pair<int,int>, compare> heap2;
	cout << "In:" << endl;
	for (int i = 0; i < TEST_SIZE; i++) {
		int x = rand() % TEST_SIZE;
		int y = rand() % TEST_SIZE;
		heap2.insert(make_pair(x, y));
		cout << "(" << x << ", " << y << ") ";
	}
	cout << endl;
	cout << "Out:" << endl;
	while (heap2.getSize() > 0) {
		pair<int, int> out = heap2.remove();
		cout << "(" << out.first << ", " << out.second << ") ";		
	}
   
	cout << endl;
	return 0;
}
