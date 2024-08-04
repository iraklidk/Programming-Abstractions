/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	currentSize = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while(head) {
		Node * tmp = head;
		head = head->next;
		delete tmp;
	}
}

int LinkedListPriorityQueue::size() {
	
	return currentSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	
	return (currentSize == 0);
}

void LinkedListPriorityQueue::enqueue(string value) {
	Node * newNode = new Node();
	newNode->val = value;
	newNode->next = NULL;
	if(head == NULL) {
		head = newNode;
		currentSize++;
		return;
	}

	if(value < head->val) {
			newNode->next = head;
			head = newNode;
			currentSize++;
			return;
	}

	Node * p = head;
	while(p->next != NULL && value > p->next->val) {
		p = p->next;
	}
	newNode->next = p->next;
	p->next = newNode;

	currentSize++;
}

string LinkedListPriorityQueue::peek() {
	if(currentSize == 0) error("Queue is an empty list");
	
	return head->val;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(currentSize == 0) error("Queue is an empty list");
	Node * tmp = head;
	head = head->next;
	string ans = tmp->val;
	delete tmp;
	currentSize--;

	return ans;
}

