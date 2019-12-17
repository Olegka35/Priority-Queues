#pragma once
#include "PriorityQueue.h"
#include <iostream>
using namespace std;

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
		this->parent = nullptr;
		this->child = nullptr;
		this->sibling = nullptr;
	}
};

template<typename T>
class BinomialHeapQueue : public PriorityQueue<T> {
public:
	BinomialHeapQueue();
	~BinomialHeapQueue();
	void insert(int key, T value) override;
	T popMin() override;
	T getMin() override;
	void remove(T value) override;
	void makeEmpty();
	void merge(PriorityQueue<T>& queue);
	bool isEmpty();

	/*void print() {
		int level = 0;
		BinomialNode<T>* tmp = root;
		while (tmp != nullptr) {
			cout << level << " [" << tmp << " : (" << tmp->key << " | " << tmp->data << ")]" << endl;
			printChildren(tmp, level);
			tmp = tmp->sibling;
		}
		cout << endl;
	}*/
private:
	BinomialNode<T> *root;
	BinomialNode<T>* mergeNodes(BinomialNode<T>* node1, BinomialNode<T>* node2);
	void insert(BinomialNode<T>* node);
	void binomial_link(BinomialNode<T>* node1, BinomialNode<T>* node2);
	BinomialNode<T>* search(T data, BinomialNode<T>* node = nullptr);
	void decrease_key(BinomialNode<T>* node, int newval = -999999999);
	void deleteNode(BinomialNode<T> *t);
	BinomialNode<T>* reverse(BinomialNode<T>* node);

	/*void printChildren(BinomialNode<T>* node, int level) {
		BinomialNode<T>* tmp = node->child;
		while (tmp != nullptr) {
			cout << level + 1 << " [" << tmp << " : (" << tmp->key << " | " << tmp->data << ")]" << endl;
			printChildren(tmp, level+1);
			tmp = tmp->sibling;
		}
	}*/
};

template<typename T>
BinomialHeapQueue<T>::BinomialHeapQueue() {
	root = nullptr;
}

template<typename T>
BinomialHeapQueue<T>::~BinomialHeapQueue() {
	makeEmpty();
}

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
	BinomialHeapQueue<T>& binomial_heap_queue = static_cast<BinomialHeapQueue<T>& >(queue);
	insert(binomial_heap_queue.root);
}

template<typename T>
void BinomialHeapQueue<T>::insert(BinomialNode<T> *node) {
	root = mergeNodes(root, node);

	BinomialNode<T> *x = root, *prev_x = nullptr, *next_x = nullptr;
	next_x = x->sibling;
	while (next_x != nullptr) {
		if ((x->degree != next_x->degree) ||
			((next_x->sibling != nullptr) && (next_x->sibling)->degree == x->degree))
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
				if (prev_x == nullptr)
					root = next_x;
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
	BinomialNode<T>* result = nullptr;
	BinomialNode<T>** pos = &result;

	while (node1 != nullptr && node2 != nullptr) {
		if (node1->degree < node2->degree) {
			*pos = node1;
			node1 = node1->sibling;
		}
		else {
			*pos = node2;
			node2 = node2->sibling;
		}
		pos = &(*pos)->sibling;
	}
	if (node1 != nullptr)
		*pos = node1;
	else
		*pos = node2;
	return result;
}

template<typename T>
void BinomialHeapQueue<T>::insert(int key, T value) {
	insert(new BinomialNode<T>(key, value));
}

template<typename T>
T BinomialHeapQueue<T>::getMin() {
	BinomialNode<T>* minNode = this->root;
	BinomialNode<T>* node = this->root;
	while (node->sibling != nullptr) {
		node = node->sibling;
		if (node->key < minNode->key)
			minNode = node;
	}
	return minNode->data;
}

template<typename T>
T BinomialHeapQueue<T>::popMin() {
	BinomialNode<T>* minNode = this->root;
	BinomialNode<T>* node = this->root;
	BinomialNode<T>* prevNode = nullptr;
	while (node->sibling != nullptr) {
		if (node->sibling->key < minNode->key) {
			prevNode = node;
			minNode = node->sibling;
		}
		node = node->sibling;
	}

	T data = minNode->data;
	node = minNode->child;
	if (prevNode == nullptr && root == minNode)
		root = minNode->sibling;
	else
		prevNode->sibling = minNode->sibling;
	if (node != nullptr) 
		insert(reverse(node));
	delete minNode;
	minNode = nullptr;
	return data;
}

template<typename T>
void BinomialHeapQueue<T>::makeEmpty() {
	//deleteNode(root);
	root = nullptr;
}

template<typename T>
void BinomialHeapQueue<T>::deleteNode(BinomialNode<T> *t) {
	if (t != nullptr) {
		deleteNode(t->child);
		deleteNode(t->sibling);
		delete t;
		t = nullptr;
	}
}

template<typename T>
void BinomialHeapQueue<T>::remove(T value) {
	BinomialNode<T>* node = search(value);
	if (node != nullptr) {
		decrease_key(node);
		popMin();
	}
}

template<typename T>
BinomialNode<T>* BinomialHeapQueue<T>::search(T data, BinomialNode<T>* node = nullptr) {
	if (node == nullptr) node = root;
	BinomialNode<T>* result = nullptr;
	if (node->data == data) {
		result = node;
		return result;
	}
	if (result == nullptr && node->child != nullptr)
		result = search(data, node->child);
	if (result == nullptr && node->sibling != nullptr)
		result = search(data, node->sibling);
	return result;
}

template<typename T>
void BinomialHeapQueue<T>::decrease_key(BinomialNode<T>* node, int newval = -999999999) {
	node->key = newval;
	while (node->parent != nullptr && node->key < node->parent->key) {
		T temp_data = node->data;
		int temp_key = node->key;
		node->data = node->parent->data;
		node->key = node->parent->key;
		node->parent->data = temp_data;
		node->parent->key = temp_key;
		node = node->parent;
	}
}

template<typename T>
bool BinomialHeapQueue<T>::isEmpty() {
	return root == nullptr;
}

template<typename T>
BinomialNode<T>* BinomialHeapQueue<T>::reverse(BinomialNode<T>* node) {
	BinomialNode<T>* tail = nullptr;
	BinomialNode<T>* next;

	if (!node)
		return node;

	node->parent = nullptr;
	while (node->sibling) {
		next = node->sibling;
		node->sibling = tail;
		tail = node;
		node = next;
		node->parent = nullptr;
	}
	node->sibling = tail;
	return node;
}