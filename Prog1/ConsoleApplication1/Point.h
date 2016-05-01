/*----------Point.h-------------

by:		Sean Webster
		16.322 Data Structures
		ECE Dept.
		UMASS Lowell

Purpose: provides interface to Point.cpp

*/

#ifndef POINT_H
#define POINT_H

struct Point
{
	double x;		// -- the x coordinate of the point
	double y;		// -- the y coordinate of the point
};

bool GetPoint(const char *promt, Point &pt);

void ShowPoint(Point pt);

#endif