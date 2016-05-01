/*--------------- P r o g 6 . c p p ---------------

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
11-22-2015	- Changes for prog6


Compiled in Visual Studio 2015 Community Edition
*/

#include <cstdlib>
#include <iostream>
#include <csetjmp>
using namespace std;

#include "CursorCntl.h"
#include "Position.h"
#include "Maze.h"

/*----- S o l v e M a z e (  ) -----

PURPOSE
Naive maze traversal algorithm. Try all possible next
positions, but give up at a dead end..

RETURN VALUE
true  -- a solution was found.
false -- failed to find a solution.
*/

bool GoalIsReachableFrom(Maze &maze, Position &curPos)
{


   // Repeatedly find a next move until the goal is reached.
		if(maze.State(curPos) != Open)
		{
			return false;
		}

		maze.Mark(curPos, Visited);				// Mark the current cell position "Visited"  

		if (curPos == maze.Goal())
		{
			gotoxy(15, 5);			// Did this instead of global constants because that's what the paper says
			cout << "Success: Found a path." << endl;
			cin.get();  // Wait for a key press.
			maze.Mark(curPos, PathCell);
			return true;
		} 
		else if (GoalIsReachableFrom(maze, curPos + StepEast))		// Recursive magic. 
		{
			maze.Mark(curPos, PathCell);		// Mark the current position a path cell
			return true;
		}
		else if (GoalIsReachableFrom(maze, curPos + StepSouth))
		{
			maze.Mark(curPos, PathCell);
			return true;
		}
		else if (GoalIsReachableFrom(maze, curPos + StepWest))
		{
			maze.Mark(curPos, PathCell);
			return true;
		}
		else if (GoalIsReachableFrom(maze, curPos + StepNorth))
		{
			maze.Mark(curPos, PathCell);
			return true;
		}
		maze.Mark(curPos, Rejected);	// Mark the current cell position "Rejected"
		return false;
		

}

/*--------------- m a i n ( ) ---------------*/

int main()
{
	// Screen positions
	const unsigned XResult = 15;
	const unsigned YResult = 5;
	const unsigned XStart = 0;;
	const unsigned YStart = 20;
	// Position 
	Position pos;   


	// Construct a maze from a maze definition file.
	Maze maze;     
	// Move to the start cell.
	pos = maze.Start();			//make the start position the current position

	// Traverse the maze.
	bool success = GoalIsReachableFrom(maze, pos);

	if (!success)
	{
		gotoxy(XResult, YResult);
		cout << "Failed: No path from start to goal exists." << endl;
	}
		
	// Indicate success or failure.

	gotoxy(XStart, YStart);
}

