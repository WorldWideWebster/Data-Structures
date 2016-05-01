/*--------------- M a z e . c p p  ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This module defines operations on objects of class Maze.

CHANGES
03-03-2015 gpc -- Created for 16.322 class.

*/

#include <limits.h>

#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <strstream>

using namespace std;

#if (!defined _WIN32) || (defined FakeNonWindows)
#include "Windows.h"
#endif

#include "Queue.h"
#include "Maze.h"
#include "CursorCntl.h"

//----- c o n s t a n t   d e f i n  t i o n s -----

const unsigned DefaultSpeed = 6; // Default speed to travel the maze
const unsigned MsPerSec = 1000;  // Number of ms. in one second
const char Quit = 'Q';           // Quit the program

// Display positions for the grid
const unsigned ColOffset = 2;		// Offset 2 columns from the left margin
const unsigned RowOffset = 2;		// Offset 2 lines from the top margin
const unsigned CellWidth = 3;		// Cell width in columns
const unsigned CellHeight = 2;  // Cell height in lines

// Symbols to display in cells
const char OpenCellSym = 'O';             // Open cell character
const char StartCellSym = 'S';            // Start cell character
const char GoalCellSym = 'G';             // Goal cell character
const char ObstacleCellSymbol[] = "##";   // Obstacle cell characters
const char PathMarkChar[] = "P ";   // Mark the path if found.


//------ f u n c t i o n    d e f i n i t i o n s -----

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
c        -- a character indicating the initial cell mark.
rowNum   -- the cell's row number
colNum   -- the cell's column number

ERRORS
Abort if more than one start or goal position are defined.  
*/

bool Maze::StoreCell(char cellStateChar, int rowNum, int colNum)
{
   // Use the character to set the initial mark of the next maze cell.
   switch (toupper(cellStateChar))
      {
      // Cell is open.
      case '0':
      case ' ':
      case OpenCellSym:
         cell[rowNum][colNum] = Open;
         break;

      // Cell is the start cell.
      case StartCellSym:
         // If start already found, quit.
         if (start.Defined())
            {
            cout << "*** ERROR: More than one start position specified." << endl;
            start.Undefine();
            goal.Undefine();
            return false;
            }

         // Mark the cell open and record the start position.
         cell[rowNum][colNum] = StartCell;
         start = Position(rowNum, colNum);
         break;

      // Cell is the goal cell.
      case GoalCellSym:
         // If goal already found, quit.
         if (goal.Defined())
            {
            cout << "*** ERROR: More than one goal position specified." << endl;
            start.Undefine();
            goal.Undefine();
            return false;
            }

         // Mark the cell open and record the goal position.
         cell[rowNum][colNum] = GoalCell;
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

bool Maze::LoadMazeFile(string &mazeFileName)
{
   // The stream from which the maze is loaded
//   string      mazeFileName;  // Maze file name
   ifstream    mazeFile;      // Maze file input stream

   // Open the maze definition file.
   OpenMazeFile(mazeFileName, mazeFile);

   // The file is open; load in the maze.

   // Read "Gridsize" lines from the file.
   for (int rowNum=0; rowNum<GridSize; rowNum++)
      {
      // Read "GridSize" columns from each line.
      for (int colNum=0; colNum<GridSize; colNum++)
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

            // Set the cell mark.
            StoreCell(cellStateChar, rowNum, colNum);
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
   const unsigned XPrompt = 0;  // Screen column for speed prompt
   const unsigned YPrompt = 23;   // Screen row for speed prompt

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
         cin.get();
         }
      else
         {
         // Not empty, read in the speed number.
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
				    gotoxy(XPrompt, YPrompt+1);
            clreol();
            cout << "***ERROR: Speed must be a positive integer." << endl;
            is.clear();
            }
         else if (speed < MinSpeed)
            {
            // The speed is too low.
				    gotoxy(XPrompt, YPrompt+1);
            clreol();
            cout << "***ERROR: Speed must be at least " << MinSpeed << "." << endl;
            }
         else
            {
            const char EnableSnd = 'S';
            // Entered speed was valid.
            needSpeed = false;
            playSounds = toupper(is.peek()) == EnableSnd;
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
   string mazeFileName;
   
   // Load the maze from the maze definition file.
   LoadMazeFile(mazeFileName);

   // Display the maze on the screen.
   Show();

   // Show the maze file name.
   const unsigned FileNameXPos = 35;
   const unsigned FileNameYPos = 0;

   gotoxy(FileNameXPos, FileNameYPos);
   cout << mazeFileName;

   // Set the speed of travel.
   SetSpeed();
}

/*----- M a z e : : S h o w (  ) -----

PURPOSE
Display the maze on the screen.
*/

void Maze::Show() const
{
   // Column numbers
   const char ColHeadings[] = "   0  1  2  3  4  5  6  7  8  9";
   const char HorizLine[] =    " +--+--+--+--+--+--+--+--+--+--+";

   // Erase the console window.
   clrscr();

   // Show column numbers above the grid.
   cout << ColHeadings << endl;
   cout << HorizLine << endl;

   // Show the grid, one row at a time.
   for (int rowNum=0; rowNum<GridSize; rowNum++)
      {
      // Give the row number to the left of the grid.
      cout << rowNum;

      // Show the next row.
      for (int colNum=0; colNum<GridSize; colNum++)
         {
         cout << '|';
         cout.width(CellWidth-1);
         switch (cell[rowNum][colNum])
            {
            case Open:
               cout << ' ';
               break;
            case StartCell:
               cout << StartCellSym;
               break;
            case GoalCell:
               cout << GoalCellSym;
               break;
            case Obstacle:
               cout << ObstacleCellSymbol;
               break;
            case PathCell:
               cout << PathMarkChar;
               break;
            default:
               cout << cell[rowNum][colNum];
               break;
            }
         }
       cout << '|';

      // Display the current position's row number beside the grid.
      int curX;
      int curY;

      getxy(curX, curY);
      gotoxy(curX+1, curY);

      cout << rowNum << endl;
      cout << HorizLine << endl;
      }

   // Show column numbers above the grid.
   cout << ColHeadings << endl;
}

/*----- M a z e : : S t a t e ( P o s i t i o n & ) -----

PURPOSE
Determine the distance of a given cell from the start cell.

INPUT PARAMETERS
cellPos  -- the position of the cell whose distance is to be
            obtained

RETURN VALUE
The cell distance.
*/

CellState Maze::State(const Position &cellPos) const
{
   // If the position is off the grid, it is illegal.
   if (cellPos.Row() < 0 || cellPos.Row() >= GridSize)
      return Obstacle;
   if (cellPos.Col() < 0 || cellPos.Col() >= GridSize)
      return Obstacle;

   // Start and goal are considered open.
   if (  cell[cellPos.Row()][cellPos.Col()] == StartCell ||
         cell[cellPos.Row()][cellPos.Col()] == GoalCell)
      return Open;

   // Use the stored cell distance.
   return cell[cellPos.Row()][cellPos.Col()];
}

/*----- M a z e : : S h o w C e l l S t a t e (  ) -----

PURPOSE
Display the distance of on cell on the screen.

INPUT PARAMETERS
p        -- the position of the cell whose cell mark is to be displayed.
dist     -- the distance to be displayed
*/

void Maze::ShowCell(const Position &p, const CellState dist) const
{
   const unsigned curPosX = 35;              // X location to display current position
   const unsigned curPosY = 2;               // Y location to display current position
   const char PathMarkChar = 'P';   // Mark the path if found.

   // Display the numeric current position (x, y).
   gotoxy( curPosX, curPosY);
   cout << "MARK  Row:    " << p.Row();
   gotoxy( curPosX, curPosY+1);
   cout << "CELL  Column: " << p.Col();

   // Display the new distance.
   gotoxy(CellWidth*p.Col() + ColOffset, CellHeight*p.Row() + RowOffset);

   cout.width(CellWidth-1);
   if (dist == PathCell)
      // If cell is on the shortest path, display the PathMarkChar.
      cout << PathMarkChar;
   else
      // Otherwise, display the cell's distance from the start.
      cout << dist;
}

/*----- M a z e : : M a r k (  ) -----

PURPOSE
Set the distance of a maze cell.

INPUT PARAMETERS
p        -- the position of the cell whose distance is to be set
dist     -- the distance from the start cell. Non-negative values
            for "dist" represent the distance of the cell being marked
            to the start cell.

            Otherwise, a cell may be marked with the negative value
            "PathCell" to indicate that it lies on the shortest path.
*/

void Maze::Mark(const Position &p, const CellState state)
{
  logFile << "Mark (" << p.Row() << ", " << p.Col() << ") = " << state << endl;

//Change the cell state.
  cell[p.Row()][p.Col()] = state;

// Check if running in Windows.
#if (!defined _WIN32) || (defined FakeNonWindows)
#ifdef LimitOutput
  if(((p == goal) && (state == Visited)) || ((p == start) && (state == PathCell)))
#endif
   // If not Windows, scroll the grid display.
   Show();
#else
   ShowCell(p, state);
#endif
   // Wait after showing the new state character.
   if (speed > 0)
     {
#if (defined _WIN32) && (!defined FakeNonWindows)
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