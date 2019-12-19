#include <iostream>
#include <cstdlib>
#include "PriorityQueue.h"
#include "LeftistQueue.h"
#include "SkewHeapQueue.h"
#include "BinomialHeapQueue.h"
#include "DHeapQueue.h"

using namespace std;

void main() {
	DHeapQueue<int> queue(3, 100);
	queue.insert(10, 10);
	queue.insert(3, 3);
	queue.insert(10, 10);
	queue.insert(10, 10);
	queue.insert(1, 1);
	queue.insert(15, 15);
	queue.insert(2, 2);

	SkewHeapQueue<int> queue2;
	queue2.insert(5, 5);
	queue2.insert(7, 7);
	queue2.insert(11, 11);
	queue2.insert(1, 1);
	queue2.remove(1);

	//queue.merge(queue2);
	
	//queue.remove(10);
	//queue.remove(10);
	//queue.remove(10);

	while (!queue.isEmpty()) {
		cout << queue.popMin() << endl;
	}
}