/*----------Point.h-------------

by:		Sean Webster
16.322 Data Structures
ECE Dept.
UMASS Lowell

Purpose: provides interface to Point.cpp

*/
using namespace std;
#ifndef POINT_H
#define POINT_H

class Point
{
	public:
		// Constructors
		Point() : defined(false)  {  }
		Point(double xVal, double yVal) : x(xVal), y(yVal), defined(true) { }
		//Accessors
		double X() const;	//returns x
		double Y() const;	//returns y
		bool Defined() { return defined; }		//returns defined
		//Mutator
		void Set(double xVal, double yVal);		//sets (x, y)
		//I/O functions
		bool Get(istream &is=cin);
		void Show(ostream &os=cout);
	private:
		double x;		// -- the x coordinate of the point
		double y;		// -- the y coordinate of the point
		bool defined;	// is defined
};
// Input-Output Operators
istream & operator>>(istream &is, Point &p);
ostream & operator<<(ostream &os, Point &p);


#endif