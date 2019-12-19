#include "PriorityQueue.h"

template<typename T>
class LeftistNode
{
public:
	int key;
	T data;
	LeftistNode<T> *left;
	LeftistNode<T> *right;
	int dist;
	LeftistNode(int key, T data, LeftistNode<T> *lt = nullptr, LeftistNode<T> *rt = nullptr, int dist = 0)
	{
		this->key = key;
		this->data = data;
		right = rt;
		left = lt;
		this->dist = dist;
	}
};


template<typename T>
class LeftistQueue : public PriorityQueue<T> {
public:
	LeftistQueue();
	~LeftistQueue();
	void insert(int key, T value) override;
	T popMin() override;
	T getMin() override;
	void remove(T value) override;
	void merge(PriorityQueue<T>& queue) override;
	void makeEmpty();
	bool isEmpty();
private:
	LeftistNode<T> *root;
	LeftistNode<T> *MergeTrees(LeftistNode<T> *h1, LeftistNode<T> *h2);
	LeftistNode<T> *MergeLeftAndRightTrees(LeftistNode<T> *h1, LeftistNode<T> *h2);
	void swapChildren(LeftistNode<T> *t);
	void removeNode(LeftistNode<T> *t);
};

template<typename T>
LeftistQueue<T>::LeftistQueue() {
	root = nullptr;
}

template<typename T>
LeftistQueue<T>::~LeftistQueue() {
	makeEmpty();
}

template<typename T>
void LeftistQueue<T>::merge(PriorityQueue<T>& queue) {
	if (this == &queue)
		return;
	LeftistQueue<T>& leftist_queue = static_cast<LeftistQueue<T>& >(queue);
	root = MergeTrees(root, leftist_queue.root);
	leftist_queue.root = nullptr;
}

template<typename T>
LeftistNode<T> *LeftistQueue<T>::MergeTrees(LeftistNode<T> *h1, LeftistNode<T> *h2) {
	if (h1 == nullptr)
		return h2;
	if (h2 == nullptr)
		return h1;
	if (h1->key < h2->key)
		return MergeLeftAndRightTrees(h1, h2);
	else
		return MergeLeftAndRightTrees(h2, h1);
}

template<typename T>
LeftistNode<T> *LeftistQueue<T>::MergeLeftAndRightTrees(LeftistNode<T> *h1, LeftistNode<T> *h2) {
	if (h1->left == nullptr)
		h1->left = h2;
	else {
		h1->right = MergeTrees(h1->right, h2);
		if (h1->left->dist < h1->right->dist)
			swapChildren(h1);
		h1->dist = h1->right->dist + 1;
	}
	return h1;
}

template<typename T>
void LeftistQueue<T>::swapChildren(LeftistNode<T> *t) {
	LeftistNode<T>* temp = t->left;
	t->left = t->right;
	t->right = temp;
}

template<typename T>
void LeftistQueue<T>::insert(int key, T value) {
	root = MergeTrees(new LeftistNode<T>(key, value), root);
}

template<typename T>
T LeftistQueue<T>::getMin() {
	return root->data;
}

template<typename T>
T LeftistQueue<T>::popMin() {
	LeftistNode<T> *oldRoot = root;
	T data = root->data;
	root = MergeTrees(root->left, root->right);
	delete oldRoot;
	return data;
}

template<typename T>
void LeftistQueue<T>::makeEmpty() {
	removeNode(root);
	root = nullptr;
}

template<typename T>
void LeftistQueue<T>::removeNode(LeftistNode<T> * t) {
	if (t != nullptr)	{
		removeNode(t->left);
		removeNode(t->right);
		delete t;
	}
}

template<typename T>
bool LeftistQueue<T>::isEmpty() {
	return root == nullptr;
}

template<typename T>
void LeftistQueue<T>::remove(T value) {
	// Нет эффективного
}