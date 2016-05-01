/*----------DblLinkedList.h-------------

by:		Sean Webster
		16.322 Data Structures
		ECE Dept.
		UMASS Lowell

Purpose: provides interface to DblLinkedList.cpp

*/
using namespace std;
#ifndef DBLLINKEDLIST_H
#define DBLLINKEDLIST_H

#include <cassert>
#include "Point.h"
// Make a type for a node's data item.
typedef Point NodeData;
//----- c l a s s D b l L i n k e d L i s t -----
class DblLinkedList
{
private:
	// List node class definition
	struct Node
	{
		NodeData data; // The "contents" of the node
		Node *pred; // Link to the predecessor node
		Node *succ; // Link to the successor node
					// Node Constructor Functions
		Node() {}
		Node(const NodeData &theData, Node *const prd = 0, Node *const suc = 0) :
			data(theData), pred(prd), succ(suc) { }
	};
public:
	// Constructor: Create an empty list.
	DblLinkedList();
	// Copy Constructor
	DblLinkedList(DblLinkedList &source);
	// Destructor
	~DblLinkedList();
	// Overloaded Assignment
	DblLinkedList operator=(DblLinkedList &rhs);
	// True if the list is empty
	bool Empty() const;
	// True if the current position is beyond the last item.
	bool AtEnd() const;
	// Rewind the current item to the beginning of the list.
	void Rewind() { current = first; }
	// Advance to the next item in the list.
	void Forward();
	// Move back to the previous entry.
	void Backward();
	// Get the contents of the current list item.
	NodeData CurrentItem() const;
	// Get the contents of the first list item.
	NodeData FirstItem() const;
	// Get the contents of the last list item.
	NodeData LastItem() const;
	// Insert a new list item before the current item.
	void InsertItem(const NodeData &d);
	// Delete the current item.
	// The new current item was the successor of the deleted item.
	void DeleteItem();
private:
	void DeepCopy(DblLinkedList &source); // Deep copy source to this object.
	Node *first; // Points to the first node in the list
	Node *last; // Points to the last node in the list
	Node *current; // Points to the current node
};




#endif DBLLINKEDLIST_H