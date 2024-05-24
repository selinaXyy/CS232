#ifndef _QUEUE
#define _QUEUE

#include "QueueInterface.h"
#include "Node.h"

class Queue : public QueueInterface {
private:
	int itemCount;
	Node* head;
	Node* current;

public:
	//constructor
	Queue();

	//queue functions
	bool isEmpty() const;
	bool enqueue(const int& newEntry);
	bool dequeue();
	int peekFront() const;
	int getItemCount() const;
	void displayQueue() const;

	//destructor
	~Queue();
};

#endif