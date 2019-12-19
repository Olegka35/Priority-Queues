#pragma once
#include "PriorityQueue.h"

template<typename T>
class DHeapData
{
public:
	int key;
	T data;

	DHeapData() {
	}

	DHeapData(int key, T data) {
		this->key = key;
		this->data = data;
	}
};

template<typename T>
class DHeapQueue : public PriorityQueue<T> {
public:
	DHeapQueue(int _d, int _capacity);
	~DHeapQueue();
	void insert(int key, T value) override;
	T popMin() override;
	T getMin() override;
	void merge(PriorityQueue<T>& queue) override;
	void remove(T value) override;
	void makeEmpty();
	bool isEmpty();
	bool isFull();

private:
	int d;
	int size;
	int capacity;
	DHeapData<T> **arr;

	int getParentIndex(int child_index);
	int getChildIndex(int parent_index, int k);
	int getSmallestChildIndex(int parent_index);
	void popUp(int index);
	void moveDown(int index);
	int search(T data);
	void deleteElement(int index);
};

template<typename T>
DHeapQueue<T>::DHeapQueue(int _d, int _capacity) {
	size = 0;
	capacity = _capacity;
	d = _d;
	arr = new DHeapData<T>*[capacity];
	for (int i = 0; i < capacity; i++)
		arr[i] = nullptr;
}

template<typename T>
DHeapQueue<T>::~DHeapQueue() {
	delete[] arr;
	arr = nullptr;
}

template<typename T>
void DHeapQueue<T>::insert(int key, T value) {
	if (isFull()) {
		return;
	}
	arr[size] = new DHeapData<T>(key, value);
	popUp(size);
	size++;
}

template<typename T>
T DHeapQueue<T>::getMin() {
	return arr[0]->data;
}

template<typename T>
T DHeapQueue<T>::popMin() {
	T data = getMin();
	deleteElement(0);
	return data;
}

template<typename T>
void DHeapQueue<T>::makeEmpty() {
	size = 0;
}

template<typename T>
void DHeapQueue<T>::remove(T value) {
	int index = search(value);
	if (index != -1) deleteElement(index);
}

template<typename T>
int DHeapQueue<T>::search(T data) {
	for (int i = 0; i < size; ++i) {
		if (arr[i]->data == data) {
			return i;
		}
	}
	return -1;
}

template<typename T>
bool DHeapQueue<T>::isEmpty() {
	return size == 0;
}

template<typename T>
bool DHeapQueue<T>::isFull() {
	return size == capacity;
}

template<typename T>
int DHeapQueue<T>::getParentIndex(int child_index) {
	return (child_index - 1) / d;
}

template<typename T>
int DHeapQueue<T>::getChildIndex(int parent_index, int k) {
	return parent_index * d + k;
}

template<typename T>
int DHeapQueue<T>::getSmallestChildIndex(int parent_index) {
	int smallestChildIndex = getChildIndex(parent_index, 1);
	int index = getChildIndex(parent_index, 2);
	for (int k = 2; k <= d && index < size; k++) {
		if (arr[index]->key < arr[smallestChildIndex]->key)
			smallestChildIndex = index;
		index = getChildIndex(parent_index, k+1);
	}
	return smallestChildIndex;
}

template<typename T>
void DHeapQueue<T>::deleteElement(int index) {
	if (isEmpty()) return;
	arr[index] = arr[size - 1];
	size--;
	moveDown(index);
}

template<typename T>
void DHeapQueue<T>::popUp(int index) {
	DHeapData<T> *data = arr[index];
	for (; index > 0 && data->key < arr[getParentIndex(index)]->key; index = getParentIndex(index))
		arr[index] = arr[getParentIndex(index)];
	arr[index] = data;
}

template<typename T>
void DHeapQueue<T>::moveDown(int index) {
	DHeapData<T> *data = arr[index];
	int child_index;
	for (; getChildIndex(index, 1) < size; index = child_index) {
		child_index = getSmallestChildIndex(index);
		if (arr[child_index]->key < data->key)
			arr[index] = arr[child_index];
		else
			break;
	}
	arr[index] = data;
}

template<typename T>
void DHeapQueue<T>::merge(PriorityQueue<T>& queue) {
	/* Нет эффективного */
}