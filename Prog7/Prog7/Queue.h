#ifndef QUEUE_H
#define QUEUE_H

/*--------------- Q u e u e. h ---------------

by:   Sean Webster

16.322 Data Structures
ECE Dept.
UMASS Lowell

PURPOSE
the interface to the queue.cpp module

*/

#include "Position.h"

typedef Position NodeData;

//********************class Queue**********************
//implements a queue of nodes
class Queue
{
	private:
		//Queue node class definition
		class Node
		{
			public:
				NodeData	data;		// The contents of the node
				Node		*next;		// Link to the next node

				// Node Constructor Functions
				Node() : next(0) {};
				Node(const NodeData &theData, Node *const theNext = 0)
					: data(theData), next(theNext) {};
		};
	public:
		Queue() : tail(0) { }		// Default constructor
		bool Empty() const { return tail == 0; };		// Return true if empty queue
		void Enqueue(const NodeData &p);				// Add item to tail
		NodeData Dequeue();								// Remove item from head
		NodeData Head() { return tail->next->data;  }	// Return the head node data	
		NodeData Tail() { return tail->data; }			// Return the tail node data
	private:
		Node *tail;
};


#endif
