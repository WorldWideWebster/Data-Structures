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
11-05-2015 gpc - Created for 16.322 class.
*/

// Include the following line to limit console output.
//#define LimitOutput

#include <fstream>
#include <string>

using namespace std;

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#endif

#include "Position.h"

//----- c o n s t a n t   d e f i n i t i o n s

const unsigned GridSize = 10;    // Number of rows and columns in the grid.

//----- t y p e    d e f i n i t  o n s -----

// Cell states are ASCII characters.
typedef char CellState;

// Define the possible states for cells in the grid.
const char Open      = ' ';
const char Obstacle  = '-';
const char Visited   = 'V';
const char Rejected  = 'R';
const char StartCell = 'S';
const char GoalCell  = 'G';
const char PathCell  = 'P';

//----- c l a s s    M a z e -----

class Maze
{
public:
   // Constructor
   Maze();

   // Destructor to close the log file.
   ~Maze() { logFile.close(); }
   
   // Accessors
   CellState State(const Position &cellPos) const;  // Return cell state
	 Position Start() const { return start; }         // Return start cell position
	 Position Goal() const { return goal; }           // Return goal cell position
   unsigned Speed() const { return speed; }
   bool PlaySounds() const { return playSounds; }

   // Mutators
   void Mark(const Position &p, CellState state);   // Mark cell at position "p"
private:
   // The square grid of maze cells
   CellState	cell[GridSize][GridSize];

   // The starting position in the maze.
   Position    start;

   // The goal position in the maze.
   Position    goal;

   // Maze File Name
   string mazeFileName;

   // The number of moves per second
   unsigned    speed;

   // True to play sounds
   bool playSounds;

   // Output stream for maze log file.
   ofstream logFile;

   // Display the maze on the screen.   
   void Show() const;

   // Display the state of one cell on the screen.
   void ShowCell(const Position &p, const CellState state) const;

   // Load the maze definition from a file.
   void OpenMazeFile(string &mazeFileName, ifstream &mazeFile);
   bool StoreCell(char c, unsigned rowNum, unsigned colNum);
   bool LoadMazeFile();

   // Set the speed of travel.
   void SetSpeed();
};


#endif