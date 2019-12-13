#pragma once
#include "PriorityQueue.h"

template<typename T>
class BinomialNode
{
public:
	int key;
	T data;
	int degree;
	BinomialNode<T> *parent;
	BinomialNode<T> *child;
	BinomialNode<T> *sibling;
	BinomialNode(int key, T data)
	{
		this->key = key;
		this->data = data;
		this->degree = 0;
		this->parent = NULL;
		this->child = NULL;
		this->sibling = NULL;
	}
};

template<typename T>
class BinomialHeapQueue : public PriorityQueue<T> {
public:
	BinomialHeapQueue();
	BinomialHeapQueue(BinomialHeapQueue<T> &rhs);
	~BinomialHeapQueue();
	void insert(int key, T value) override;
	T popMin() override;
	T getMin() override;
	//void remove(T value) override;
	void makeEmpty();
	void merge(PriorityQueue<T>& queue);
	bool isEmpty();
private:
	BinomialNode<T> *root;
	BinomialNode<T> *rootr;
	BinomialNode<T>* mergeNodes(BinomialNode<T>* node1, BinomialNode<T>* node2);
	int count;
	void binomial_link(BinomialNode<T>* node1, BinomialNode<T>* node2);
};

template<typename T>
BinomialHeapQueue<T>::BinomialHeapQueue() {
	root = NULL;
	rootr = NULL;
	count = 1;
}

/*template<typename T>
BinomialHeapQueue<T>::SkewHeapQueue(BinomialHeapQueue<T> &rhs) {
	root = NULL;
	*this = rhs;
}

template<typename T>
BinomialHeapQueue<T>::~BinomialHeapQueue() {
	makeEmpty();
}*/

template<typename T>
void BinomialHeapQueue<T>::binomial_link(BinomialNode<T>* node1, BinomialNode<T>* node2) {
	node1->parent = node2;
	node1->sibling = node2->child;
	node2->child = node1;
	node2->degree = node2->degree + 1;
}

template<typename T>
void BinomialHeapQueue<T>::merge(PriorityQueue<T>& queue) {
	if (this == &queue)
		return;
	BinomialHeapQueue<T>& skep_heap_queue = static_cast<BinomialHeapQueue<T>& >(queue);
	root = mergeNodes(root, queue->root);
	
	BinomialNode<T>* x = root, prev_x = NULL, next_x = NULL;
	next_x = x->sibling;
	while (next_x != NULL) {
		if ((x->degree != next_x->degree) || 
			((next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree))
		{
			prev_x = x;
			x = next_x;
		}
		else {
			if (x->key <= next_x->key) {
				x->sibling = next_x->sibling;
				binomial_link(next_x, x);
			}
			else {
				if (prev_x == NULL)
					H = next_x;
				else
					prev_x->sibling = next_x;
				binomial_link(x, next_x);
				x = next_x;
			}
		}
		next_x = x->sibling;
	}
}

template<typename T>
BinomialNode<T>* BinomialHeapQueue<T>::mergeNodes(BinomialNode<T> *node1, BinomialNode<T> *node2) {
	if (node1 == NULL)
		return node2;
	if (node2 == NULL)
		return node1;

	BinomialNode<T>* result;
	BinomialNode<T>* x = node1;
	BinomialNode<T>* y = node2;
	if (x->degree <= y->degree)
		result = x;
	else
		result = y;
	
	while (x != NULL && y != NULL) {
		if (x->degree < y->degree)
			x = x->sibling;
		else if (x->degree == y->degree) {
			BinomialNode<T>* a = x->sibling;
			x->sibling = y;
			x = a;
		}
		else {
			BinomialNode<T>* b = y->sibling;
			y->sibling = x;
			y = b;
		}
	}
	return result;
}

template<typename T>
void BinomialHeapQueue<T>::insert(int key, T value) {
	merge(new BinomialNode<T>(key, value), root);
}

template<typename T>
T BinomialHeapQueue<T>::getMin() {
	return root->data;
}

template<typename T>
T BinomialHeapQueue<T>::popMin() {
	SkewNode<T> *oldRoot = root;
	T data = root->data;
	root = MergeTrees(root->left, root->right);
	delete oldRoot;
	return data;
}

template<typename T>
void BinomialHeapQueue<T>::makeEmpty() {
	deleteNode(root);
	root = NULL;
}

template<typename T>
void BinomialHeapQueue<T>::deleteNode(SkewNode<T> *t) {
	if (t != NULL) {
		deleteNode(t->left);
		deleteNode(t->right);
		delete t;
	}
}

template<typename T>
bool BinomialHeapQueue<T>::isEmpty() {
	return root == NULL;
}