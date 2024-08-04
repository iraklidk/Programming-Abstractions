/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	
}

HeapPriorityQueue::~HeapPriorityQueue() {
	
}

int HeapPriorityQueue::size() {
	
	return priorityQueue.size();
}

bool HeapPriorityQueue::isEmpty() {
	
	return size() == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	priorityQueue.push_back(value);
	if(size() <= 1) return;
	int idx = size() - 1;
	int parIdx = idx / 2;
	if(idx % 2 == 0) parIdx--;
	while(priorityQueue[parIdx] > priorityQueue[idx]) {
		swap(priorityQueue[parIdx], priorityQueue[idx]);
		idx = parIdx;
		parIdx = idx / 2;
		if(idx % 2 == 0 && idx != 0) parIdx--;
	}
}

string HeapPriorityQueue::peek() {
	if(size() == 0) error("Queue is empty");

	return priorityQueue[0];
}

string HeapPriorityQueue::dequeueMin() {
	if(size() == 0) error("Queue is empty");
	string ans = priorityQueue[0];
	swap(priorityQueue[0], priorityQueue[size() - 1]);
	priorityQueue.remove(size()-1);

	int idx = 0;
	int leftIdx = 2 * idx + 1;
	int rightIdx = 2 * idx + 2;

	while(leftIdx < size() && rightIdx < size()) {
		int minIdx = 0;
		if(priorityQueue[leftIdx] < priorityQueue[rightIdx]) 
			minIdx = leftIdx;
		else
			minIdx = rightIdx;

		if(priorityQueue[idx] > priorityQueue[minIdx]) {
			swap(priorityQueue[idx], priorityQueue[minIdx]);
			idx = minIdx;
			leftIdx = 2 * minIdx + 1;
			rightIdx = 2 * minIdx + 2;
		}
		// [a, b, c, d, e, f, g]
		// [g, b, c, d, e, f]
		else break;
	}

    if (leftIdx < size()) {
        if (priorityQueue[idx] > priorityQueue[leftIdx]) {
            std::swap(priorityQueue[idx], priorityQueue[leftIdx]);
        }
    }

	return ans;
}

