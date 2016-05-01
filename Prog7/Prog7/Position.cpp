/*--------------- P o s i t i o n . c p p  ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This module defines operations on objects of class Position.

CHANGES
03-03-2015 gpc -- Created for 16.322 class.
*/

#include <iostream>
#include <cassert>

using namespace std;

#include "CursorCntl.h"
#include "Position.h"

// Instantiate a static data member mirror the queue on the screen.
Position Position::mirror[MirrorCap];

// Instantiate a static data member to count on screen queue length.
unsigned Position::length;

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

const unsigned XQueue = 40;
const unsigned YQueue = 16;
const unsigned ElemPerLine = 19;

/*----- S h o w M i r r o r ( ) -----

PURPOSE
Display the queue mirror array on the screen.
*/
void Position::ShowMirror()
{
   // Display the row number.
   gotoxy(XQueue + 2 , YQueue);
   clreol();
   
   for (unsigned i=0; i<length; i++)
     cout << " " << mirror[i].Row();

   // Display the column number.
   gotoxy(XQueue + 2, YQueue + 1);
   clreol();

   for (unsigned i=0; i<length; i++)
     cout << " " << mirror[i].Col();
}

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
   if (length == 0)
      {
      gotoxy(XQueue, YQueue);
      os << "R";
      gotoxy(XQueue, YQueue+1);
      os << "C";
      }

   // Add the new position to the mirror array.
   mirror[length++] = *this;

   // Show the mirror array.
   ShowMirror();
   
   // Restore the saved screen position.
   RestoreXY();
}

/*----- P o s i t i o n : : U n S h o w ( ) -----

PURPOSE
Remove the last displayed position.

INPUT PARAMETERS
os -- the stream on which the position was displayed.
*/

void Position::UnShow()
{
   SaveXY();

   // Remove the oldest position from the mirror array.
   --length;
   for (unsigned i=0; i<length; i++)
     mirror[i] = mirror[i+1];
    
   // Show the mirror array.
   ShowMirror();
   
   // Restore the saved screen position.
  RestoreXY();
}