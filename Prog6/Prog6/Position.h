#ifndef POSITION_H
#define POSITION_H
/*--------------- P o s i t i o n . h ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This is the interface to Position.cpp.

CHANGES
11-05-2015 gpc - Created for 16.322 class.
*/

#include <iostream>
#include <string>

using namespace std;

//----- c l a s s    P o s i t i o n -----
class Position
{
public:
   // static data member to count on screen stack depth
   static unsigned level;
   static void ResetLevel() { level = 0; }
   // Constructors
   Position() {defined = false; }
   Position(int theRow, int theCol) : row(theRow), col(theCol), defined(true) { }
   // Accessors
   int Row() const { return row; }
   int Col() const { return col; }
   bool Defined() { return defined; }
   // Mutators
   void Undefine() { defined = false; }
   // Position Output
   void Show(ostream &os);
   void UnShow(ostream &os);
   // Overloaded operators
   Position operator+(const Position &b) const;
   Position operator+=(const Position &b);
   bool operator!=(const Position &b) const { return (row!=b.row) || (col!=b.col); }
   bool operator==(const Position &b) const { return (row==b.row) && (col==b.col); }
private:
   int	row;      // the row (y) location of a position
   int	col;      // the column (x) location of a position
   bool     defined;  // True if the position has been defined
};
// Offsets to neighboring cells (relative positions)
const Position StepEast = Position(0, +1);   // One step east
const Position StepSouth = Position(+1, 0);  // One step south
const Position StepWest = Position(0, -1);   // One step west
const Position StepNorth = Position(-1, 0);  // One step north

void ResetLevel();
#endif