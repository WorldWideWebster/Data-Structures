/*--------------- S t a c k . c p p ---------------

by:   Sean Webster

	16.322 Data Structures
	ECE Dept.
	UMASS Lowell

PURPOSE
Stack class to hold positions in maze

*/

#include "stack.h"
#include <cassert>

/*----- Stack::Push() -----

PURPOSE
Push a new element onto the stack

*/

void Stack::Push(const StackElement &p)
{
	Node *temp;
	assert(temp = new(nothrow) Node(p, top));
	top = temp;
	temp = 0;
	delete temp;
}

/*----- Stack::Pop() -----

PURPOSE
Pop the top element off of the stack

RETURN VALUE
new top element
*/
StackElement Stack::Pop()
{
	if(!Empty())
	{
		Node *temp;
		assert(temp = new(nothrow) Node(top->data, 0));
		temp = top;
		top = top->next;
		return temp->data;
	}
	
}