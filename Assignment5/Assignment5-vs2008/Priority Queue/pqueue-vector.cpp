/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	
}

VectorPriorityQueue::~VectorPriorityQueue() {
	
}

int VectorPriorityQueue::size() {
	
	return priorityQueue.size();
}

bool VectorPriorityQueue::isEmpty() {

	return size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {

	priorityQueue.push_back(value);
}

string VectorPriorityQueue::peek() {
	if(isEmpty()) error("You are trying to dequeue an empty queue");
	string ans = "";
	for(int i = 0; i < size(); i++) {
		if(priorityQueue[i] > ans) ans = priorityQueue[i];
	}

	return ans;
}

string VectorPriorityQueue::dequeueMin() {
	if(isEmpty()) error("You are trying to dequeue an empty queue");
	string ans = "";
	int idx = 0;
	for(int i = 0; i < size(); i++) {
		if(priorityQueue[i] > ans) {
			ans = priorityQueue[i];
			idx = i;
		}
	}
	priorityQueue.remove(idx);
	
	return ans;;
}

