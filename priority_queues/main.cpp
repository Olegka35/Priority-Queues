#include <iostream>
#include <cstdlib>
#include "PriorityQueue.h"
#include "LeftistQueue.h"
#include "SkewHeapQueue.h"
#include "BinomialHeapQueue.h"

using namespace std;

void main() {
	SkewHeapQueue<int> queue;
	queue.insert(10, 10);
	queue.insert(3, 3);
	queue.insert(10, 10);
	queue.insert(10, 10);
	queue.insert(1, 1);
	queue.insert(15, 15);
	queue.insert(2, 2);

	while (!queue.isEmpty()) {
		cout << queue.popMin() << endl;
	}
}