#ifndef _NODE
#define _NODE

class Node {
private:
	int item;
	Node* next;

public:
	//constructors
	Node();
	Node(const int& itemPar);
	Node(const int& itemPar, Node* nextNodePar);

	//getters & setters
	int getItem() const;
	Node* getNextNode() const;
	void setItem(const int& itemPar);
	void setNextNode(Node* nextNodePar);
};

#endif