#include "Queue.h"
#include "Node.h"
#include <iostream>
using namespace std;

Queue::Queue() {
	itemCount = 0;
	head = new Node();
	current = head;
}

bool Queue::isEmpty() const {
	return itemCount == 0;
}

bool Queue::enqueue(const int& newEntry) {
	if (itemCount == 0 && newEntry >= 0) {
		current->setItem(newEntry);
		itemCount++;
		return true;
	}
	else if (newEntry >= 0) {
		Node* newNode = new Node(newEntry);
		current->setNextNode(newNode);
		current = newNode;
		itemCount++;
		return true;
	}
	else
		return false;
}

bool Queue::dequeue() {
	if (!isEmpty()) {
		head = head->getNextNode();
		itemCount--;
		return true;
	}
	else
		return false;
}

int Queue::peekFront() const {
	return head->getItem();
}

int Queue::getItemCount() const {
	return itemCount;
}

void Queue::displayQueue() const {
	Node* current = head;
	while (current != nullptr) {
		cout << current->getItem() << " ";
		current = current->getNextNode();
	}
}

Queue::~Queue() {
	Node* current = head;
	while (current != nullptr) {
		Node* nodeToDelete = current;
		current = current->getNextNode();
		delete nodeToDelete;
		nodeToDelete = nullptr;
	}
	delete current;
	delete head;
	head = nullptr;
}