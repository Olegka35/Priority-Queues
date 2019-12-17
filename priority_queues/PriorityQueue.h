#pragma once

template<typename T>
class PriorityQueue {
public:
	virtual ~PriorityQueue(){}

	virtual void insert(int key, T value) = 0;
	virtual T popMin() = 0;
	virtual T getMin() = 0;
	virtual void remove(T value) = 0;
	virtual void merge(PriorityQueue<T>& queue) = 0;
	virtual bool isEmpty() = 0;
};