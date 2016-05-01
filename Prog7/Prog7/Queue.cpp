/*--------------- Q u e u e . c p p ---------------

by:   Sean Webster

16.322 Data Structures
ECE Dept.
UMASS Lowell

PURPOSE
Fuction definitions for queue class

-------------------------------------------------------------*/

#include "Queue.h"
#include<iostream>
#include<cassert>
using namespace std;


/*----- Queue::Enqueue()  -------------------------------------

PURPOSE
Add a new node at tail of queue

-------------------------------------------------------------*/

void Queue::Enqueue(const NodeData &p) 
{
	Node *newTail;
	assert(newTail = new(nothrow) Node(p));
	if(Empty())											// Case of empty list
	{
		newTail->next = newTail;
	}
	else												// Not empty list
	{
		newTail->next = tail->next;
		tail->next = newTail;
	}

	tail = newTail;
}

/*----- Queue::Dequeue()  -------------------------------------

PURPOSE
Remove node at head and return data

-------------------------------------------------------------*/

NodeData Queue::Dequeue()
{
	NodeData oldHead = Head();	// grab current head data before deleting it
	assert(!Empty());
	if (tail == tail->next)		// Single node in queue
	{
		delete tail;			// Creates empty list
		tail = 0;
	}

	else
	{
		Node *currHead = tail->next;		// Current head node
		tail->next = currHead->next;		//	Remove current head
		delete currHead;
	}
	return oldHead;
}

