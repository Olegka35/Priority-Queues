#pragma once
#include "PriorityQueue.h"

template<typename T>
class SkewNode
{
public:
	int key;
	T data;
	SkewNode<T> *left;
	SkewNode<T> *right;
	SkewNode(int key, T data, SkewNode<T> *lt = nullptr, SkewNode<T> *rt = nullptr)
	{
		this->key = key;
		this->data = data;
		right = rt;
		left = lt;
	}
};

template<typename T>
class SkewHeapQueue : public PriorityQueue<T> {
public:
	SkewHeapQueue();
	~SkewHeapQueue();
	void insert(int key, T value) override;
	T popMin() override;
	T getMin() override;
	//void remove(T value) override;
	void makeEmpty();
	void merge(PriorityQueue<T>& queue);
	bool isEmpty();
private:
	SkewNode<T> *root;
	SkewNode<T> *MergeTrees(SkewNode<T> *h1, SkewNode<T> *h2);
	void deleteNode(SkewNode<T> *t);
};

template<typename T>
SkewHeapQueue<T>::SkewHeapQueue() {
	root = nullptr;
}

template<typename T>
SkewHeapQueue<T>::~SkewHeapQueue() {
	makeEmpty();
}

template<typename T>
void SkewHeapQueue<T>::merge(PriorityQueue<T>& queue) {
	if (this == &queue)
		return;
	SkewHeapQueue<T>& skew_heap_queue = static_cast<SkewHeapQueue<T>& >(queue);
	root = MergeTrees(root, skew_heap_queue.root);
	skew_heap_queue.root = nullptr;
}

template<typename T>
SkewNode<T> *SkewHeapQueue<T>::MergeTrees(SkewNode<T> *h1, SkewNode<T> *h2) {
	if (h1 == nullptr)
		return h2;
	if (h2 == nullptr)
		return h1;
	
	if (h1->key <= h2->key) {
		SkewNode<T>* temp = h1->right;
		h1->right = h1->left;
		h1->left = MergeTrees(temp, h2);
		return h1;
	}
	else
		return MergeTrees(h2, h1);
}

template<typename T>
void SkewHeapQueue<T>::insert(int key, T value) {
	root = MergeTrees(new SkewNode<T>(key, value), root);
}

template<typename T>
T SkewHeapQueue<T>::getMin() {
	return root->data;
}

template<typename T>
T SkewHeapQueue<T>::popMin() {
	SkewNode<T> *oldRoot = root;
	T data = root->data;
	root = MergeTrees(root->left, root->right);
	delete oldRoot;
	return data;
}

template<typename T>
void SkewHeapQueue<T>::makeEmpty() {
	deleteNode(root);
	root = nullptr;
}

template<typename T>
void SkewHeapQueue<T>::deleteNode(SkewNode<T> *t) {
	if (t != nullptr) {
		deleteNode(t->left);
		deleteNode(t->right);
		delete t;
	}
}

template<typename T>
bool SkewHeapQueue<T>::isEmpty() {
	return root == nullptr;
}