/*--------------- M a z e . c p p  ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This module defines operations on objects of class Maze.

CHANGES
11-05-2015 gpc - Created for 16.322 class.
*/

#include <climits>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <strstream>
#include <csetjmp>
#include <ctime>
#include <cstdlib>


using namespace std;

#include "Maze.h"
#include "CursorCntl.h"

//----- c o n s t a n t   d e f i n  t i o n s -----

const unsigned DefaultSpeed = 6;  // Default speed to travel the maze
const unsigned MsPerSec = 1000;   // Number of ms. in one second
const char Quit = 'Q';            // Quit the program


//------ f u n c t i o n s -----

/*----- M a z e : : O p e n M a z e F i l e (  ) -----

PURPOSE
Open a maze definition file.

OUTPUT PARAMETERS
mazeFileName   -- a string giving the name of the opened file
mazeFile       -- the opened stream
*/

void Maze::OpenMazeFile(string &mazeFileName, ifstream &mazeFile)
{
   const char DefFileName[] = "maze"; // Default maze definition file name
   const string ext = ".txt";         // Maze definition file extension

   // Repeatedly ask for a file name and try to open it.
   for(;;)
      {
      // Get the file name. If empty, use the default.
      cout << "Maze file name [default = \"" << DefFileName << "\", 'Q' quits]: ";
      if (cin.peek()=='\n')
         {
         cin.ignore(INT_MAX, '\n');
         mazeFileName = DefFileName;
         }
      else
         {
         getline(cin, mazeFileName);
         if ((mazeFileName.length() == 1) && (toupper(mazeFileName[0]) == Quit))
           exit(EXIT_SUCCESS);
         }

      // Insure that the file extension is correct.
      if (mazeFileName.length() >= ext.length())
         {
         if (mazeFileName.substr(mazeFileName.length()-ext.length()) != ext)
            mazeFileName += ext;
         }
      else
         mazeFileName += ext;

      // Try to open the file.
      mazeFile.open(mazeFileName.c_str());

      // If success, open a log file.
      if (mazeFile.is_open())
          {
          const string LogFileExt = ".log";  // Log file extension

          // The log file name is the same as the maze file name
          // with the extension changed to ".log."

          string logFileName = mazeFileName;

          logFileName.erase(logFileName.length()- ext.length(), ext.length());

          logFileName += LogFileExt;

         
          logFile.open(logFileName.c_str());

          // Make sure the log file opened.
          assert(logFile.is_open());

          break;
          }

      // Open failed: clear the stream state, give an error message, and try again.
      mazeFile.clear();
      cout << "*** ERROR: No such file: " << mazeFileName << endl;
      }
}

/*----- M a z e : : S t o r e C e l l (  ) -----

PURPOSE
Initialize one cell in the maze.

INPUT PARAMETERS
c        -- a character indicating the initial cell state.
rowNum   -- the cell's row number
colNum   -- the cell's column number

ERRORS
Abort if more than one start or goal position are defined.  
*/

bool Maze::StoreCell(char cellStateChar, unsigned rowNum, unsigned colNum)
{
   // Use the character to set the initial state of the next maze cell.
   switch (toupper(cellStateChar))
      {
      // Cell is open if cellStateChar is digit zero, space, or letter 'O'.
      case '0':
      case ' ':
      case 'O':
         cell[rowNum][colNum] = Open;
         break;

      // Cell is the start cell.
      case StartCell:
         // If start already found, quit.
         if (start.Defined())
            {
            cout << "*** ERROR: More than one start position specified." << endl;
            start.Undefine();
            goal.Undefine();
            return false;
            }

         // Mark the cell and record the start position.
         cell[rowNum][colNum] = StartCell;	// 10-16-2003 gpc
         start = Position(rowNum, colNum);
         break;

      // Cell is the goal cell.
      case GoalCell:
         // If goal already found, quit.
         if (goal.Defined())
            {
            cout << "*** ERROR: More than one goal position specified." << endl;
            start.Undefine();
            goal.Undefine();
            return false;
            }

         // Mark the cell and record the goal position.
         cell[rowNum][colNum] = GoalCell;	//0-16-2003 - gpc
         goal = Position(rowNum, colNum);
         break;

      // Any other character represents an obstacle.
      default:
         cell[rowNum][colNum] = Obstacle;
         break;
      }
  return true;
}

/*----- M a z e : : L o a d M a z e F i l e (  ) -----

PURPOSE
Initialize the maze from a maze definition file.

ERRORS
Abort if incomplete maze, or no start or goal position are defined.
*/

bool Maze::LoadMazeFile()
{
   // The stream from which the maze is loaded
   ifstream    mazeFile;      // Maze file input stream

   // Open the maze definition file.
   OpenMazeFile(mazeFileName, mazeFile);

   // The file is open; load in the maze.

   // Read "Gridsize" lines from the file.
   for (unsigned rowNum=0; rowNum<GridSize; rowNum++)
      {
      // Read "GridSize" columns from each line.
      for (unsigned colNum=0; colNum<GridSize; colNum++)
        {
        char  cellStateChar;    // the next character from the file

        // Get the next character.
        mazeFile.get(cellStateChar);

        // If early end-of-file reached, abort.
        if (mazeFile.eof())
            {
            cout << "*** ERROR: Unexpected end of file on " << mazeFileName << endl;
            start.Undefine();
            goal.Undefine();
            return false;
            }

        // Set the cell state.
        if (!StoreCell(cellStateChar, rowNum, colNum))
          return false;
        }
         
      // Flush newline before reading the next line from the file.
      mazeFile.ignore(INT_MAX, '\n');
      }

   // Done with the file, close it.
   mazeFile.close();

   // Make sure that the file contained start and goal positions.
   if (!start.Defined())
      {
      cout << "*** ERROR: No start positon specified." << endl;
      start.Undefine();
      goal.Undefine();
      return false;
      }

   if (!goal.Defined())
      {
      cout << "*** ERROR: No goal positon specified." << endl;
      start.Undefine();
      goal.Undefine();
      return false;
      }
   return true;
}

/*----- M a z e : : S e t S p e e d (  ) -----

PURPOSE
Get the maze travel speed.
*/

void Maze::SetSpeed()
{
   const unsigned MinSpeed = 0;  // Speed must be bigger than zero.
   const unsigned DefSpeed = 6;  // Default speed setting
   const unsigned XPrompt = 0;   // Screen column for speed prompt
   const unsigned YPrompt = 15;  // Screen row for speed prompt

   bool  needSpeed;     // True until a valid speed is entered.

   // Repeatedly ask for a speed until a valid value is given.
   do
      {
      // Read the speed.
      needSpeed = true;
      gotoxy(XPrompt, YPrompt);
      clreol();
      cout << "Speed [minimum = " << MinSpeed << " (<ENTER> to single step), default = " << DefSpeed << ", 'Q' quits]: ";

      if (cin.peek() == '\n')
         {
         // If empty, use the default.
         speed = DefaultSpeed;
         needSpeed = false;
         cin.ignore(INT_MAX, '\n');
         }
      else
         {
         string speedString;
         getline(cin, speedString);
         if ((speedString.length() == 1) && (toupper(speedString[0]) == Quit))
           exit(EXIT_SUCCESS);
         // Not empty, read in the speed number.
         istrstream is(speedString.c_str());
         is >> speed;

         // Make sure the speed is valid.
         if (is.fail())
            {
            // A bad integer was entered.
            clreol();
            cout << "***ERROR: Speed must be a non-negative integer." << endl;
            cin.clear();
            }
         else if (speed < MinSpeed)
            {
            // The speed is too low.
            clreol();
            cout << "***ERROR: Speed must be at least " << MinSpeed << "." << endl;
            }
         else
            {
            // Entered speed was valid.
            needSpeed = false;
            playSounds = toupper(is.peek()) == 'S';
            }

         }
      }
   while (needSpeed);

   // Clean up any remaining error messages.
   gotoxy(XPrompt, YPrompt+1);
   clreol();
}

/*----- M a z e : : M a z e (  ) -----

PURPOSE
Construct a Maze object from a maze definition file.
*/

Maze::Maze()
{
   // Load the maze from the maze definition file.
   while (!LoadMazeFile())
    ;

   // Display the maze on the screen.
   Show();

   // Set the speed of travel.
   SetSpeed();
}

/*----- M a z e : : S h o w (  ) -----

PURPOSE
Display the maze on the screen.
*/

void Maze::Show(void) const
{
   // Column numbers
   const char ColHeadings[] = " 0123456789";

   // Erase the console window.
   clrscr();

   // Show column numbers above the grid.
   cout << ColHeadings << "    " << mazeFileName << endl;

   // Show the grid, one row at a time.
   for (unsigned rowNum=0; rowNum<GridSize; rowNum++)
      {
      // Give the row number to the left of the grid.
      cout << rowNum;

      // Show the next row.
      for (unsigned colNum=0; colNum<GridSize; colNum++)
         cout << cell[rowNum][colNum];

      // Give the row number to the left of the grid.
      cout << rowNum << endl;
      }

   // Show column numbers above the grid.
   cout << ColHeadings << endl;
}

/*----- M a z e : : S t a t e ( P o s i t i o n & ) -----

PURPOSE
Determine the state of a given maze cell.

INPUT PARAMETERS
cellPos  -- the position of the cell whose state is to be
            obtained

RETURN VALUE
The cell state.
*/

CellState Maze::State(const Position &cellPos) const
{
   // If the position is off the grid, it is illegal.
   if (cellPos.Row() < 0 || cellPos.Row() >= GridSize)
      return Obstacle;
   if (cellPos.Col() < 0 || cellPos.Col() >= GridSize)
      return Obstacle;

   // The start and goal cells are open until visited.
   if (cell[cellPos.Row()][cellPos.Col()] == StartCell)
      return Open;
   if (cell[cellPos.Row()][cellPos.Col()] == GoalCell)
      return Open;

   // Use the stored cell state.
   return cell[cellPos.Row()][cellPos.Col()];
}

/*----- M a z e : : S h o w C e l l (  ) -----

PURPOSE
Display the state of on cell on the screen.

INPUT PARAMETERS
p        -- the position of the cell whose state is to be displayed.
state    -- the state to be displayed
*/

void Maze::ShowCell(const Position &p, const CellState state) const
{
   const unsigned CurPosX = 15;           // X location to display current position
   const unsigned CurPosY = 2;            // Y location to display current position

   // Display the numeric current position (x, y).
   gotoxy(CurPosX, CurPosY);
   cout << "CURRENT  Row:    " << p.Row();
   gotoxy(CurPosX, CurPosY+1);
   cout << "POSITON  Column: " << p.Col();

   // Display the new state.
   gotoxy(p.Col()+1, p.Row()+1);

   // Wait and then change and display the new state character.
//   Delay(MsPerSec/speed);

   cout << state;
}

/*----- M a z e : : M a r k (  ) -----

PURPOSE
Mark a maze cell visited.

INPUT PARAMETERS
p        -- the position of the cell to mark
state    -- the state with which to mark the cell
*/
void Maze::Mark(const Position &p, CellState state)
{
  logFile << "Mark (" << p.Row() << ", " << p.Col() << ") = " << state << endl;

//Change the cell state.
  cell[p.Row()][p.Col()] = state;

// Check if running in Windows.
#if (!defined _WIN32) || (defined NoGraphics)
#ifdef LimitOutput
  if(((p == goal) && (state == Visited)) || ((p == start) && (state == PathCell)))
#endif
   // If not Windows, scroll the grid display.
   Show();
#else
   // If Windows, uses console window cursor control graphics.
  ShowCell(p, state);
#endif
   // Wait after showing the new state character.
   if (speed > 0)
     {
#if (defined _WIN32) && (!defined NoGraphics)
      // Windows has a Sleep() function.
      Sleep(MsPerSec/speed);
#else
      // Not Windows, use ctime.h to delay.
      time_t tStart = clock();

      while ((float)(clock()-tStart)/(float)CLOCKS_PER_SEC < 1/(float)speed)
        ;
#endif
     }
   else
      // Speed = 0, so single step.
      cin.get();
}
