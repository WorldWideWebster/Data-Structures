#ifndef CURSORCNTL_H
#define CURSORCNTL_H
/*--------------- C u r s o r C n t l . h ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This is the interface to CursorCntl.cpp.

CHANGES
03-03-2015 gpc -- Created for 16.322 class.
*/

// To simulate not running in Windows, include the following line.
//#define FakeNonWindows

//----- f u n c t i o n    p r o t o t y p e s

void getxy(int &x, int &y);
void gotoxy(int x, int y);
void clrscr ();
void clreol ();
void SaveXY();
void RestoreXY();
#endif

