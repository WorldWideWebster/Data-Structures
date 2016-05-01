/*--------------- P r o g 5 . c p p ---------------

by:   Sean Webster
	  George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
Find a path through a maze.

CHANGES
11-05-2015 gpc - Created for 16.322 class.
11-15-2015, msot of program done
11-17-2015 - final changes


Compiled in Visual Studio 2015 Community Edition
*/

#include <cstdlib>
#include <iostream>
#include <csetjmp>
using namespace std;

#include "CursorCntl.h"
#include "Position.h"
#include "Maze.h"
#include "Stack.h"

/*----- S o l v e M a z e (  ) -----

PURPOSE
Naive maze traversal algorithm. Try all possible next
positions, but give up at a dead end..

RETURN VALUE
true  -- a solution was found.
false -- failed to find a solution.
*/

bool SolveMaze(Maze &maze, Stack &stack)
{
   Position curPos;     //create a position stack

   // Move to the start cell.
   curPos = maze.Start();			//make the start position the current position
   maze.Mark(curPos, Visited);		// Mark the current cell position "Visited"  
   //stack.Push(maze.Start());
   // Repeatedly find a next move until the goal is reached.
   while (curPos != maze.Goal())
      {
		  if (maze.State(curPos + StepEast) == Open)
		  {
			  stack.Push(curPos);			// Push current cell position on the stack
			  curPos += StepEast;
			  
			  maze.Mark(curPos, Visited);				// Mark the current cell position "Visited"  
		  }
		  else if (maze.State(curPos + StepSouth) == Open)
		  {
			  stack.Push(curPos);			// Push current cell position on the stack
			  curPos += StepSouth;
			  
			  maze.Mark(curPos, Visited);	// Mark the current cell position "Visited"
		  }
		  else if (maze.State(curPos + StepWest) == Open)
		  {
			  stack.Push(curPos);			// Push current cell position on the stack
			  curPos += StepWest;
			  
			  maze.Mark(curPos, Visited);	// Mark the current cell position "Visited"
		  }
		  else if (maze.State(curPos + StepNorth) == Open)
		  {
			  stack.Push(curPos);			// Push current cell position on the stack
			  curPos += StepNorth;
			  
			  maze.Mark(curPos, Visited);	// Mark the current cell position "Visited"
		  }
		  else
		  {				
			  maze.Mark(curPos, Rejected);	// Mark the current cell position "Rejected"
			  if (stack.Empty())			
				  return false;
			  curPos = stack.Pop();			// pop current cell position on the stack
		  }
      }
   stack.Push(curPos);					// Push the goal onto the stack
   return true;
}

/*--------------- m a i n ( ) ---------------*/

int main()
{
	// Screen positions
	const unsigned XResult = 15;
	const unsigned YResult = 5;
	const unsigned XStart = 0;;
	const unsigned YStart = 20;
	// Position stack remembers visited positons.
	Stack posStack;   

  // Save the environment for longjmp() to restore.

//Comes here when setjmp() returns zero

	  // Construct a maze from a maze definition file.
	  Maze maze;     
   
		// Traverse the maze.
		bool success = SolveMaze(maze, posStack);
		// Indicate success or failure.
		gotoxy(XResult, YResult);
		if (!success)
			cout << "Failed: No path from start to goal exists." << endl;
		else
		  {
			cout << "Success: Found a path." << endl;
			cin.get();  // Wait for a key press.
			
      // Retrace the path back to the goal.
			while (!posStack.Empty())
			   maze.Mark(posStack.Pop(), PathCell);
			}
		// Reset cursor screen location.
		gotoxy(XStart, YStart);
}

