#ifndef MAZE_H
#define MAZE_H
/*--------------- M a z e . h ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This is the interface to Maze.cpp.

CHANGES
03-03-2015 gpc -- Created for 16.322 class.
*/


#include <fstream>
#include <string>

using namespace std;

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#endif

#include "Position.h"
#include "Queue.h"

//----- c o n s t a n t   d e f i n i t i o n s

const unsigned GridSize = 10;    // Number of rows and columns in the grid.

//----- t y p e    d e f i n i t  o n s -----

// Cell states are integers.
typedef int CellState;

// Define the possible states for cells in the grid.
// Note that a non-negative cell state gives the distance of that cell
// from the start cell.
const int Open     = -1;	// Cell is open
const int Obstacle = -2;	// Cell is an obstacle
const int StartCell= -3;	// Cell is the start cell
const int GoalCell = -4;	// Cell is the goal cell
const int PathCell = -5;	// Cell is on the shortest path

//----- c l a s s    M a z e -----

class Maze
{
public:
   // Constructor
   Maze();
   
   // Destructor to close the log file.
   ~Maze() { logFile.close(); }
   
   // Accessors
   CellState State(const Position &p) const;            // State of cell at "p"
	 Position Start() { return start; }                   // Start cell position
	 Position Goal() { return goal; }                     // Goal cell position
   unsigned Speed() const { return speed; }             // Move speed
   bool PlaySounds() const { return playSounds; }       // True if sound enabled

   // Mutators
   void Mark(const Position &p, const CellState dist);  // Mark cell "p" with "dist"
   void CloseLog() { logFile.close(); }
private:
   // The square grid of maze cells
   CellState	cell[GridSize][GridSize];

   // The starting position in the maze.
   Position    start;

   // The goal position in the maze.
   Position    goal;

   // The number of moves per second
   unsigned     speed;

   // True to play sounds
   bool         playSounds;

   // Output stream for maze log file.
   ofstream     logFile;

   // Display the maze on the screen.   
   void Show() const;

   // Show one cell on the screen.
   void ShowCell(const Position &p, const CellState state) const;

   // Load the maze definition from a file.
   void OpenMazeFile(string &mazeFileName, ifstream &mazeFile);
   bool StoreCell(char c, int rowNum, int colNum);
   bool LoadMazeFile(string &mazeFileName);

   // Set the speed of travel.
   void SetSpeed();
};


#endif