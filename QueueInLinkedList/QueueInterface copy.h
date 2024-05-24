#ifndef _QUEUE_INTERFACE
#define _QUEUE_INTERFACE

class QueueInterface {
public:
	virtual bool isEmpty() const = 0;
	virtual bool enqueue(const int& newEntry) = 0;
	virtual bool dequeue() = 0;
	virtual int peekFront() const = 0;
};

#endif