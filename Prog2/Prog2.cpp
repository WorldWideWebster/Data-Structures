/*--------------- P r o g 2 . c p p ---------------


by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This is the main program module for Program 2.

1. Read inn the definition of a piecewise linear function from the keyboard.
2. Augment the function by reading in one more point.
3. Read in the range of t over which the function is to be displayed.
4. Display the interpolated function.

CHANGES
09-22-2015 gpc -- Distribute to 16.322 class.
*/

#include <iostream>

using namespace std;

#include "Point.h"
#include "PwlFcn.h"

/*--------------- m a i n ( ) ---------------*/

int main()
{
  PwlFcn theFcn;     // The piecewise linear function

  // Read in and display the initial function definition.
  cout << "ENTER A FUNCTION DEFINITION: " << endl;
  cin >> theFcn;
  if (!(theFcn.NumPts() > 0))
      return 0;
  cout << endl << "Here is the function definition:" << endl;
  cout << theFcn;

  // Now, augment the function definition by adding one more point.  
  cout << "\nEnter one more point: ";
  Point newPt;
  cin >> newPt;
  
  // If a new point was added, display the augmented function.  
  if (newPt.Defined())
    {
    theFcn = theFcn + newPt;
    cout << "\nHere is the augmented function definition:" << endl;
    cout << theFcn;
    }
    
  // Read in the start time.
  double tStart;
  cout << endl << "What is the start time? " ;
  cin >> tStart;

  // Read in the end time.
  double tEnd;
  cout << endl << "What is the end time? " ;
  cin >> tEnd;

  // Read in the number of points to display.
  double numPts;
  cout << endl << "How many points? " ;
  cin >> numPts;
  
  // Calculate dt;
  double dt = (tEnd - tStart) / (numPts - 1);

  // Finally, display the interpolated waveform.
  cout << endl << "Here is the interpolated waveform:" << endl;
  for (unsigned i=0; i<numPts; i++)
     {
     // Compute and display the location of the next point.
     Point nextPt;
     double t = tStart + i*dt;

     nextPt.Set(t, theFcn.Interpolate(t));
     cout << nextPt << endl;
     }

  return 0;
}
 