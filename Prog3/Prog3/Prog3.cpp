/*--------------- P r o g 3 . c p p ---------------

by:   Sean Webster
      16.322 Data Structures
      ECE Department
      UMASS Lowell

	  Written in Visual Studio 2015

PURPOSE
This is an interactive arbitrary function generator. A piecewise linear function
defining one cycle of a periodic waveform may be entered from either the keyboard
or from a text file. Then, upon command, the program will generate the periodic
waveform from tStart to tEnd using numPts equally spaced points.

DEMONSTRATES
Doubly Linked Lists

               
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

#include "Point.h"
#include "DblLinkedList.h"

//----- c o n s t a n t    d e f i n i t i o n s -----

// Command Letters
const char BackwardCmd ='B';  // Move the current item back one entry.
const char ClearCmd =   'C';  // Make the pwlFcn empty
const char DeleteCmd =  'D';  // Delete the current point from the pwlFcn.
const char ForwardCmd = 'F';  // Move the current item forward one entry.
const char GenerateCmd ='G';  // Generate the waveform
const char InsertCmd =  'I';  // Insert a new point in the pwlFcn.
const char OpenCmd =    'O';  // Read in a pwlFcn from a file.
const char PrintCmd =   'P';  // Show the pwlFcn on the display.
const char QuitCmd =    'Q';  // Quit
const char RewindCmd =  'R';  // Rewind the current point to the first point in the function definition.
const char SaveAsCmd =  'S';  // Write the pwlFcn to a file.

//----- f u n c t i o n    p r o t o t y p e s -----

string GetCmd(DblLinkedList &pwlFcn);
void InsertPoint(const string cmdLine, DblLinkedList &pwlFcn);
void ClearPwlFcn(DblLinkedList &pwlFcn);
void Generate(string cmdLine, DblLinkedList &pwlFcn);
string GetFileName(string cmdLine);
void ReadPwlFcnFile(string cmdLine, DblLinkedList &pwlFcn);
void WritePwlFcnFile(string cmdLine, DblLinkedList &pwlFcn);
void DisplayPwlFcn(DblLinkedList &pwlFcn);
double Interpolate(DblLinkedList &pwlFcn, double x);

//--------------- m a i n ( ) ---------------

int main()
{
  DblLinkedList  pwlFcn;   // The pwlFcn list
  string cmdLine;          // The current command line
  bool quitCmd = false;    // true to quit

  // Repeatedly get a command from the keyboard and
  // execute it.
  do
    {
    cmdLine = GetCmd(pwlFcn);
    if (cmdLine.length() != 0)
      {
      switch (toupper(cmdLine[0]))
        {
        // Determine which command to execute.
        case InsertCmd:        // Insert a new point.
          InsertPoint(cmdLine, pwlFcn);
          break;
        case ClearCmd:      // Clear the pwlFcn.
          ClearPwlFcn(pwlFcn);
          break;
        case DeleteCmd:     // Delete the current point.
          if (!pwlFcn.AtEnd())
            pwlFcn.DeleteItem();
          if (pwlFcn.Empty())
            cout << "The pwlFcn is empty." << endl;
          break;
        case PrintCmd:       // Display the pwlFcn.
          DisplayPwlFcn(pwlFcn);
          break;
        case OpenCmd:       // Read in a pwlFcn file.
          ReadPwlFcnFile(cmdLine, pwlFcn);
          break;
        case SaveAsCmd:      // Write out a pwlFcn file.
          WritePwlFcnFile(cmdLine, pwlFcn);
          break;
        case ForwardCmd:       // Advance to the next point.
          if (!pwlFcn.AtEnd())
            pwlFcn.Forward();
          if (pwlFcn.AtEnd())
            cout << "The pwlFcn is at the end." << endl;
          break;
        case BackwardCmd:       // Go back to the previous point.
          pwlFcn.Backward();
          break;
        case RewindCmd:
          pwlFcn.Rewind();
          break;
        case GenerateCmd:     // Generate waveform.
          Generate(cmdLine, pwlFcn);
          break;
        case QuitCmd:       // Terminate execution.
          quitCmd = true;
          break;
        default:            // Bad command
          cout << "*** Error: Unknown Command" << endl;
          break;
        }
      }
    }
  while (!quitCmd);

  return 0;
}



/*--------------- G e t C m d ( ) ---------------

PURPOSE
Accept a command from the keyboard.

INPUT PARAMETERS
pwlFcn      -- the pwlFcn list.

RETURN VALUE
The command letter.
*/
string GetCmd(DblLinkedList &pwlFcn)
{
  // Display the current point before accepting each command.
  if (!pwlFcn.AtEnd())
    {
    // Display the current item.
    cout << "\nCURRENT ITEM" << endl;
  
    cout << pwlFcn.CurrentItem();

    cout << endl;
    }

  // Prompt for a new command.
  cout << "\n>";

  string cmdLine;    // Command line

  // Get the next command and return it.
  getline(cin, cmdLine);

  return cmdLine;
}

/*--------------- I n s e r t P o i n t ( ) ---------------

PURPOSE
Insert a new point in the pwlFcn before the current point.

INPUT PARAMETERS
cmdLine -- the execute command command line.
pwlFcn  -- the pwlFcn list.
*/
void InsertPoint(string cmdLine, DblLinkedList &pwlFcn)
{
  const unsigned  MinCmdSize = 2; // To check for an empty insert command

  Point             point;                // New pwlFcn point
  
  istringstream     cmdStream(cmdLine.erase(0,1));   // Command stream

  // Ignore if empty add parameters.
  if (cmdLine.length() < MinCmdSize)
    return;
      
  // Read the new point and insert it into the pwlFcn.
  cmdStream >> point;

  pwlFcn.InsertItem(point);
}


/*--------------- G e n e r a t e ( ) ---------------

PURPOSE
Generate the periodic function.

INPUT PARAMETERS
cmdLine -- the execute command command line.
pwlFcn  -- the pwlFcn list.
*/
void Generate(string cmdLine, DblLinkedList &pwlFcn)
{
   // Make sure the function is defined.
   if (pwlFcn.Empty())
      {
      cout << "The pwlFcn is empty." << endl;
      return;
      }
   Point testPoint;   // The point to test
   const unsigned  MinCmdSize = 2; // Check empty test command
   istringstream   cmdStream(cmdLine.erase(0,1)); // Cmd stream

   // Ignore if empty test parameters.
   if (cmdLine.length() < MinCmdSize)
      return;
      
   // Read the start and stop times and the number of points.
   double tStart;
   double tEnd;
   unsigned numPts;

   cmdStream >> tStart >> tEnd >> numPts;
   
   double dt = (tEnd - tStart) / (numPts - 1);

   // Generate the waveform starting at t = 0.
   double t = tStart;
   
   pwlFcn.Rewind();
   
   for (unsigned i=0; i<numPts; i++)
      {
      Point pt = Point(t, Interpolate(pwlFcn, t));
      
      cout << pt << endl;
      
      t += dt;
      }
   
   pwlFcn.Rewind();
}  

/*--------------- G e t F i l e N a m e ( ) ---------------

PURPOSE
Read a file name from the keyboard.

INPUT PARAMETERS
cmdLine -- the execute command command line.

RETURN VALUE
the file name or empty string if cancelled.
*/
string GetFileName(string cmdLine)
{
  string        fileName;           // The file name
  istringstream cmdStream(cmdLine.erase(0,1)); // Make a command stream.

  // Ignore empty file name
  if (cmdLine.length() == 0)
    return "";

  // Advance over whitespace.
  while (isspace(cmdStream.peek()))
    cmdStream.get();

  // Get the file name and return it.
  getline(cmdStream, fileName);

  return fileName;
}

/*--------------- R e a d P w l F c n F i l e ( ) ---------------

PURPOSE
Read in a pwlFcn file.

INPUT PARAMETERS
cmdLine -- the execute command command line.
pwlFcn  -- the pwlFcn list.
*/
void ReadPwlFcnFile(string cmdLine, DblLinkedList &pwlFcn)
{
  ifstream  pwlFcnStream;  // The input stream
  string    pwlFcnFile;    // The input file name

  // Ask for the file name and then open the file.
  pwlFcnFile = GetFileName(cmdLine);
  if (pwlFcnFile.length() == 0)
    return;

  pwlFcnStream.open(pwlFcnFile.c_str());
  if (!pwlFcnStream.is_open())
    {
    cout << "*** ERROR: No such file " << pwlFcnFile << endl;
    return;
    }

  // Read in the entire pwlFcn file.
  while (pwlFcnStream.peek() != EOF)
    {
    Point point; // Next input point

    pwlFcnStream >> point;
    pwlFcn.InsertItem(point);
    }
  pwlFcnStream.close();
   
  pwlFcn.Rewind();
}


/*--------------- W r i t e P w l F c n F i l e ( ) ---------------

PURPOSE
Write out a pwlFcn file.

INPUT PARAMETERS
cmdLine -- the execute command command line.
pwlFcn  -- the pwlFcn list.
*/
void WritePwlFcnFile(string cmdLine, DblLinkedList &pwlFcn)
{
  ofstream  pwlFcnStream;  // The output stream
  string    pwlFcnFile;    // The output file name

  // Ask for the file name and then open the file.
  pwlFcnFile = GetFileName(cmdLine);

  if (pwlFcnFile.length() == 0)
    return;

  pwlFcnStream.open(pwlFcnFile.c_str());

  if (!pwlFcnStream.is_open())
    {
    cout << "*** ERROR: Failed to open file " << pwlFcnFile << endl;
    return;
    }

  // Write out the entire pwlFcn.
  pwlFcn.Rewind();
  while (!pwlFcn.AtEnd())
    {
    pwlFcnStream << pwlFcn.CurrentItem().X() <<" " << pwlFcn.CurrentItem().Y() << endl;
    pwlFcn.Forward();
    }
      
  pwlFcn.Rewind();
}

/*--------------- D i s p l a y P w l F c n ( ) ---------------

PURPOSE
Display a pwlFcn from beginning to end.

INPUT PARAMETERS
pwlFcn  -- the pwlFcn to be displayed.
*/
void DisplayPwlFcn(DblLinkedList &pwlFcn)
{
	pwlFcn.Rewind();
	while (!pwlFcn.AtEnd())
	{
		cout << pwlFcn.CurrentItem();
		pwlFcn.Forward();
	}
	pwlFcn.Rewind();
}

/*--------------- C l e a r P w l F c n ( ) ---------------

PURPOSE
Make the pwlFcn empty.

INPUT PARAMETERS
pwlFcn  -- the pwlFcn list.
*/
void ClearPwlFcn(DblLinkedList &pwlFcn)
{
	pwlFcn.Rewind();
	while (!pwlFcn.AtEnd())
	{
		pwlFcn.DeleteItem();
	}

}

/*--------------- I n t e r p o l a t e ( ) ---------------

PURPOSE
Determine the value of the waveform at time t by linear interpolation.

INPUT PARAMETERS
pwlFcn  -- the pwlFcn list
t       -- the time at which the waveform value is to be obtained
*/
double Interpolate(DblLinkedList &pwlFcn, double t)
{
	Point curr;			// curr node
	Point next;			// next node 
	double slope;		// delta-y over delta-x
	double intercept;	// y intercept
	Point last = pwlFcn.LastItem();
	Point first = pwlFcn.FirstItem();
	double length = last.X() - first.Y();
	pwlFcn.Rewind(); 

	while ((t < first.X()) || (t > last.X()))		// for repeating functions/functions outside of scope
	{ 
		if (t < first.X()) 
		{
			t = t + (abs(length));
		}
		else if (t > last.X()) 
		{
			t = t - (abs(length));
		}
	}
	while (!pwlFcn.AtEnd()) 
	{
		curr = pwlFcn.CurrentItem();
		pwlFcn.Forward();
		next = pwlFcn.CurrentItem();
		if (t > curr.X() && t < next.X())			// push t to the limits! (is t between each node)
		{ 
			slope = (next.Y() - curr.Y()) / (next.X() - curr.X());
			intercept = curr.Y() - (slope * curr.X());
			break;
		}
		else if (t == curr.X() || t == next.X())	// t = current node means no slope
		{ 
			if (t == curr.X())
				intercept = curr.Y();
			else
				intercept = next.Y();
			slope = 0;
			break;
		}
	}
	return ((slope * t) + intercept);		// return Y
}