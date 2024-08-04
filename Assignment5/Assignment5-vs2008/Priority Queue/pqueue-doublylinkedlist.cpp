/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	currentSize = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while(head) {
		Node * tmp = head;
		head = head->next;
		delete tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	
	return currentSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	
	return currentSize == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	currentSize++;
	Node * newNode = new Node();
	newNode->val = value;
	newNode->prev = NULL;
	
	if(head == NULL) {
		newNode->next = NULL;
	}else {
		newNode->next = head;
		newNode->next->prev = newNode;
	}
	head = newNode;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(currentSize == 0) error("Queue is empty");
	Node * tmp = head;
	string minima = head->val;

	while(tmp != NULL) {
		if(tmp->val < minima) {
			minima = tmp->val;
		}
		tmp = tmp->next;
	}

	return minima;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(currentSize == 0) error("Queue is empty");
	string ans = peek();
	currentSize--;
	Node * tmp = head;
	while(tmp->val != ans) {
		tmp = tmp->next;
	}
	if(tmp->prev != NULL && tmp->next != NULL) {
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	else if(tmp->prev == NULL && tmp->next == NULL) {
		head = NULL;
	}
	else if(tmp->prev == NULL && tmp->next != NULL) {
		tmp->next->prev = NULL;
		head = tmp->next;
	}
	else if(tmp->prev != NULL && tmp->next == NULL) {
		tmp->prev->next = NULL;
	}

	delete tmp;
	return ans;
}

