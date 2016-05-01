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


bool Point::Get(istream &is)
 {

	 if (is.peek() != '\n')
	 {
		 is >> x >> y;
		 defined = true;
	 }
	 else
		 defined = false;
	is.ignore(INT_MAX, '\n');
	return defined;

}


/*-------------------Show-----------------

PURPOSE
Show x and y of a particular point

OUTPUT PARAMETERS
Point data x and y are shown on screen

*/

void Point::Show(ostream &os) //displays cartesian coordinates given a Point
{
	os << "(" << x << ", " << y << ")"; // << endl;
}


/*-------------------Sset-----------------

PURPOSE
Set x and y of a particular point

OUTPUT PARAMETERS
Point data x and y are set in class

*/

void Point::Set(double xVal, double yVal)
{
	x = xVal;
	y = yVal;
}

/*-------------------Operators-----------------

PURPOSE
Overloaded operators for Point class

*/

istream & operator>>(istream &is, Point &p)
{
	p.Get(is);

	return is;
}
ostream & operator<<(ostream &os, Point &p)
{
	p.Show(os);

	return os;
}