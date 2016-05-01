/*--------------- P r o g 7 . c p p ---------------

by:   Sean Webster
	  George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
Find the shortest path through a maze.

CHANGES
03-03-2015 gpc -- Created for 16.322 class.
12-15-2015		  Finished for class

compiled in visual studio 2015 community edition
*/

#include <cstdlib>
#include <iostream>

using namespace std;

#include "CursorCntl.h"
#include "Maze.h"
#include "Position.h"

/*----- S o l v e M a z e (  ) ------------------------------

PURPOSE
Attempt to find the shortest path through the maze.

INPUT PARAMETERS
maze           -- the maze object to be traversed
positionQueue  -- the queue of current and future positions

RETURN VALUE
true  -- a path was found.
false -- failed to find a path.
-------------------------------------------------------------*/
bool SolveMaze(Maze &maze, Queue &positionQueue)
{
	maze.Mark(maze.Start(), 0);					// Mark the maze start with distance 0
	positionQueue.Enqueue(maze.Start());		// Add maze start to queue
	CellState distance = 0;						// cell distance from start

	while (!positionQueue.Empty())
	{
		while (((maze.State(positionQueue.Head() + StepEast)) == Open)			// While head position has any unmarked neighbors
			|| ((maze.State(positionQueue.Head() + StepSouth)) == Open) 
			|| ((maze.State(positionQueue.Head() + StepWest)) == Open) 
			|| ((maze.State(positionQueue.Head() + StepNorth)) == Open)) 	
		{
			distance = maze.State(positionQueue.Head());										// Set distance

			if ((maze.State(positionQueue.Head() + StepEast)) == Open)							// Is east cell open?
			{
				maze.Mark(positionQueue.Head() + StepEast, distance + 1);						// Mark cell with proper distance
				if ((positionQueue.Head() + StepEast) == maze.Goal())							// Is open cell the goal?
					return true;
				
				positionQueue.Enqueue(positionQueue.Head() + StepEast);							// Add it to the queue
			}
			else if ((maze.State(positionQueue.Head() + StepSouth)) == Open)					// Is south cell open?
			{
				maze.Mark(positionQueue.Head() + StepSouth, distance + 1);						// Mark cell with proper distance
				if ((positionQueue.Head() + StepSouth) == maze.Goal())							// Is open cell the goal?
					return true;
				
				positionQueue.Enqueue(positionQueue.Head() + StepSouth);						// Add it to the queue
			}
			else if ((maze.State(positionQueue.Head() + StepWest)) == Open)						// Is West cell open?
			{
				maze.Mark(positionQueue.Head() + StepWest, distance + 1);						// Mark cell with proper distance
				if ((positionQueue.Head() + StepWest) == maze.Goal())							// Is open cell the goal?
					return true;
				
				positionQueue.Enqueue(positionQueue.Head() + StepWest);							// Add it to the queue
			}
			else if ((maze.State(positionQueue.Head() + StepNorth)) == Open)					// Is North cell open?
			{
				maze.Mark(positionQueue.Head() + StepNorth, distance + 1);						// Mark cell with proper distance
				if ((positionQueue.Head() + StepNorth) == maze.Goal())							// Is open cell the goal?
					return true;
				
				positionQueue.Enqueue(positionQueue.Head() + StepNorth);						// Add it to the queue
			}
		}
		positionQueue.Dequeue();
	}
	return false;
}

/*----- R e t r a c e (  ) ----------------------------------

PURPOSE
Mark the path from the goal to the start cell.

INPUT PARAMETERS
maze           -- the maze object to be marked
-------------------------------------------------------------*/
void Retrace(Maze &maze)
{
 
	Position curPos = maze.Goal();
	int distance = maze.State(maze.Goal());		// Distance from start cell

	while (distance >= 0)
	{
		maze.Mark(curPos, PathCell);
		if ((maze.State(curPos + StepNorth)) == (distance - 1))
			curPos = curPos + StepNorth;
		
		else if ((maze.State(curPos + StepWest)) == (distance - 1))
			curPos = curPos + StepWest;
		
		else if ((maze.State(curPos + StepSouth)) == (distance - 1))
			curPos = curPos + StepSouth;
		
		else if ((maze.State(curPos + StepEast)) == (distance - 1))
			curPos = curPos + StepEast;

		distance -= 1;
	}
}

/*--------------- m a i n ( ) ---------------*/

void main(void)
{
   // Screen positions
   const unsigned XResult = 35;
   const unsigned YResult = 5;
   const unsigned XFinish = 35;
   const unsigned YFinish = 10;

	// Queue of future positions to visit
	Queue positionQueue;

	// Construct a maze from a maze definition file.
	Maze  maze;

	// Solve the maze.
	bool success = SolveMaze(maze, positionQueue);

	// Indicate success or failure.
	gotoxy(XResult, YResult);

	if (!success)
		cout << "Failed: No path from start to goal exists." << endl;
	else
		{
		cout << "Success: Found the shortest path." << endl;
		gotoxy(XResult, YResult+2);
		cout << "Press ENTER to highlight the shortest path.";
		cin.get();

   // Retrace the path back to the goal.
		Retrace(maze);
		}

	// Done traversal
	gotoxy(XFinish, YFinish);
}
