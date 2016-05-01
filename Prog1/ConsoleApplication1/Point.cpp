/*----------Point.cpp-------------

by:		Sean Webster
		16.322 Data Structures
		ECE Dept.
		UMASS Lowell

Purpose: Defines functions to work on point structure

*/



#include <iostream>
#include <cmath>
#include "Point.h"

using namespace std;

int numPoints = 0; // for differing between first and subsequent points

/*-------------------GetPoint-----------------

PURPOSE
Get x and y of a particular point

OUTPUT PARAMETERS
Point data x and y are gathered and sent to struct

RETURN VALUES
boolean tellign whether point was read
*/


bool GetPoint(const char *promt, Point &pt)
{
	bool gotPoint = false;
	cout << promt;	
	if (cin.peek() != '\n')
	{
		cin >> pt.x >> pt.y;
		gotPoint = true;
	}
	cin.ignore(INT_MAX, '\n');
	return gotPoint;
	
}


/*-------------------ShowPoint-----------------

PURPOSE
Show x and y of a particular point

OUTPUT PARAMETERS
Point data x and y are shown on screen

*/

void ShowPoint(Point pt) //displays cartesian coordinates given a Point
{
	cout << "(" << pt.x << ", " << pt.y << ")" << endl;
}



