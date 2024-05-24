#include "Node.h"

Node::Node() {
	item = 0;
	next = nullptr;
}

Node::Node(const int& itemPar) {
	if (itemPar > 0)
		item = itemPar;
	else
		item = 0;
	next = nullptr;
}

Node::Node(const int& itemPar, Node* nextNodePar) {
	if (itemPar > 0)
		item = itemPar;
	else
		item = 0;

	next = nextNodePar;
}

int Node::getItem() const {
	return item;
}

Node* Node::getNextNode() const {
	return next;
}

void Node::setItem(const int& itemPar) {
	if (itemPar > 0)
		item = itemPar;
	else
		item = 0;
}

void Node::setNextNode(Node* nextNodePar) {
	next = nextNodePar;
}