/*----------DblLinkedList.cpp-------------

by:		Sean Webster
		16.322 Data Structures
		ECE Dept.
		UMASS Lowell

Purpose: Defines functions to work on peicewise linear function

*/
#include <iostream>
#include "Point.h"
#include <cassert>
#include "DblLinkedList.h"


using namespace std;
/*
Type "DblLinkedList" represents a piecewise-linear function as a sequence of points by doubly linked lists
*/


//-------------------  DblLinkedList::DblLinkedList() -------------------
// Basic Constructor
DblLinkedList::DblLinkedList()
{
	first = 0;
	current = 0;
	last = 0;
}

//-------------------  DblLinkedList::DblLinkedList() -------------------
// Constructor with deep copy
DblLinkedList::DblLinkedList(DblLinkedList &source)
{
	first = 0;
	current = 0;
	last = 0;
	DeepCopy(source);
}

//---------------------DblLinkedList::~DblLinkedList()--------------
// Destructor
DblLinkedList::~DblLinkedList()
{
	Rewind();
	while (current != 0)
		DeleteItem();
}

///-------------------  DblLinkedList::Empty() -------------------
// True if the list is empty
bool DblLinkedList::Empty() const 
{
	return (first == 0);
}

//-------------------  DblLinkedList::AtEnd() -------------------
// True if the current position is beyond the last defined entry.
bool DblLinkedList::AtEnd() const 
{
	return (current == 0);
}

//-------------------  DblLinkedList::Forward() -------------------
//Advance to the next item in the list
void DblLinkedList::Forward()
{
	assert(!AtEnd());
	if (!AtEnd())
	{
		current = current->succ;
	}
}

//-------------------  DblLinkedList::Backward() -------------------
// Move back to the previous entry
void DblLinkedList::Backward()
{
	if (current != first && current != 0)
	{
		current = current->pred;
	}
	else if (current == 0)
	{
		current = last;
	}
}

//-------------------  DblLinkedList::CurrentItem() -------------------
// Get the contents of the first list item
NodeData DblLinkedList::CurrentItem() const
{
	assert(current);	
	if (current != 0)
	{
		return current->data;
	}
}

//-------------------  DblLinkedList::FirstItem() -------------------
// Get the contents of the First list item
NodeData DblLinkedList::FirstItem() const
{
	assert(first);
	return first->data;
}

//-------------------  DblLinkedList::LastItem() -------------------
// Get the contents of the last list item
NodeData DblLinkedList::LastItem() const
{
	assert(last);
	return last->data;
}
//-------------------  DblLinkedList::InsertItem() -------------------
// Insert a new list entry before the current entry.
void DblLinkedList::InsertItem(const NodeData &d)
{
	Node *newNode;
	if (Empty())		//Empty List
	{
		assert(newNode = new(nothrow) Node(d, 0, 0));
		first = newNode;
		last = newNode;
	}

	else if (current == first)		// first Item in list
	{
		assert(newNode = new(nothrow) Node(d, 0, first));
		first = newNode;
	}
	else if (current != 0 && current != first)		//Middle of list 
	{
		assert(newNode = new(nothrow) Node(d, current->pred, current));
		current->pred->succ = newNode;
		current->pred = newNode;
	}
	else if (current == 0)		// End of list
	{
		assert(newNode = new(nothrow) Node(d, last, current));
		last->succ = newNode;
		last = newNode;
	}
}

//-------------------  DblLinkedList::DeleteItem() -------------------
//Delete the current entry.
void DblLinkedList::DeleteItem() {
	//Node *tempNode;
	assert(current);
	if (first == last)
	{		// One node in list
		delete current;
		first = 0;
		last = 0;
		current = 0;
	}
	else if (current == first) 
	{               //Delete the first node
		first = current->succ;
		delete current;
		current = first;
	}
	else if (current == last) 
	{               //Delete the last node
		
		current = current->pred;	
		current->succ = 0;
		delete last;
		last = current;
		current = last->succ;
		
	}
	else if (current->pred !=0 && current->succ != 0)
	{		//Delete in middle
		current->pred->succ = current->succ;
		current->succ->pred = current->pred;
		
		current = current->succ;
		//delete tempNode;
		
	}
	else if (first == last) 
	{		// One node in list
		delete current;
		first = 0;
		last = 0;
		current = 0;
	}
	else if (current == 0) // Empty List
	{
		cout << "Cannot delete current point\n";
	}

	
}

//-------------------  DblLinkedList::operator=() -------------------
//Overloaded = operator
DblLinkedList DblLinkedList::operator=(DblLinkedList &rhs)
{
	if (this != &rhs)
	{
		DeepCopy(rhs);	//Deletes AND Copies! Wow!
	}
	return *this;
}

//-------------------  DblLinkedList::DeepCopy() -------------------
// Deep copy source to this object
void DblLinkedList::DeepCopy(DblLinkedList &source)
{
	Node *tempNode;
	assert(tempNode = new(nothrow) Node());
	tempNode = source.current;
	//Delete the old list
	this->~DblLinkedList();
	//Rewind the source list
	source.Rewind();
	//Copy that linked list.
	while (source.current != 0)
	{
		InsertItem(source.CurrentItem());
		source.Forward();
	}
	source.current = tempNode;
	current = tempNode;
	tempNode = 0;
	delete tempNode;
}
