/*--------------- P o s i t i o n . c p p  ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This module defines operations on objects of class Position.

CHANGES
11-05-2015 gpc - Created for 16.322 class.
*/

#include <iostream>
#include <cassert>

using namespace std;

#include "CursorCntl.h"
#include "Position.h"

// Instantiate a static data member to count on screen stack depth
unsigned Position::level;

/*----- P o s i t i o n : : o p e r a t o r + ( ) -----

PURPOSE
Add two positions by adding the row numbers and adding the
column numbers.

INPUT PARAMETERS
b  -- the second operand of "+"
*/

Position Position::operator+(const Position &b) const
{
   Position result;

   result.row = row + b.row;
   result.col = col + b.col;
   result.defined = true;

   return result;
}

/*----- P o s i t i o n : : o p e r a t o r + = ( ) -----

PURPOSE
Add position "b" to this position.

INPUT PARAMETERS
b  -- the second operand of "+="
*/

Position Position::operator+=(const Position &b)
{
   row = row + b.row;
   col = col + b.col;
   defined = true;

   return *this;
}

// Control screen display of the stack.
const unsigned XStack = 0;        // Screen column to start stack display
const unsigned YStack = 17;       // Screen row to start stack display
const unsigned ElemPerLine = 39;  // Number of stack elements per line

/*----- P o s i t i o n : : S h o w ( ) -----

PURPOSE
Display a position at a screen location to the right
of the last display.

INPUT PARAMETERS
os -- the stream on which the position is to be displayed.
*/

void Position::Show(ostream &os)
{
   // Save the current screen position.
   SaveXY();

   // Display labels if this is the first time.
   if (level == 0)
      {
      gotoxy(XStack, YStack);
      os << "R";
      gotoxy(XStack, YStack+1);
      os << "C";
      }

   // Display the row and column numbers on successive lines
   // at an increasing distance from the left margin.
   gotoxy(XStack + 2 + 2*(level%ElemPerLine), YStack + 2*(level / ElemPerLine));

   os << row;

   gotoxy(XStack + 2 + 2*(level%ElemPerLine), YStack+1 + 2*(level / ElemPerLine));

   os << col;

   // Raise the display level.
   level++;

   // Restore the saved screen position.
   RestoreXY();
}

/*----- P o s i t i o n : : U n S h o w ( ) -----

PURPOSE
Remove the last displayed position.

INPUT PARAMETERS
os -- the stream on which the position was displayed.
*/

void Position::UnShow(ostream &os)
{
   // Save the current screen position.
   SaveXY();

   //Lower the display level.
   --level;

   // Erase the rightmost position display.
   gotoxy(XStack + 2 + 2*(level%ElemPerLine), YStack + 2*(level / ElemPerLine));
   os << " ";
   gotoxy(XStack + 2 + 2*(level%ElemPerLine), YStack+1 + 2*(level / ElemPerLine));
   os << " ";

   // Restore the saved screen position.
  RestoreXY();
}