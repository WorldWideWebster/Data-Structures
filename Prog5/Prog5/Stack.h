/*--------------- S t a c k . h ---------------

by:   Sean Webster

16.322 Data Structures
ECE Dept.
UMASS Lowell

PURPOSE
the interface to the stack.cpp module

*/


#ifndef STACK_H
#define STACK_H
#include "position.h"
#include <cassert>

typedef Position StackElement;

class Stack
{
	// List node class definition
	struct Node
	{
		Node(const StackElement &theData, Node *const nxt = 0)
			: data(StackElement(theData)), next(nxt) { }

		StackElement	data;	// The contents of the node
		Node			*next;	// Link to the next node
	};
public:
	Stack() { top = 0;}														//constructor function
	bool Empty() const { return top == 0; }									//Empty function
	StackElement Top() const { assert(!Empty()); return top->data; }		//Top return function
	void Push(const StackElement &p);										//Push function
	StackElement Pop();														//Pop function
private:	
	Node *top;

};

#endif