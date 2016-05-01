/*----------PwlFcn.h-------------

by:		Sean Webster
		16.322 Data Structures
		ECE Dept.
		UMASS Lowell

Purpose: provides interface to PwlFcn.cpp

*/

#ifndef PWLFCN_H
#define PWLFCN_H

const unsigned MaxPts = 10; // Maximum points in a function definition
/*
Type "PwlFucn" represends a piecewise-linear function as a sequence of points
*/

struct PwlFcn
{
	unsigned numPts;			// -- Number of points in the function
	Point pt[MaxPts];			// -- List of points defining the function
};

//---------Function Prototypes---------------
bool GetF(const char *prompt, PwlFcn &f);
void ShowF(PwlFcn &f);
double Interpolate(PwlFcn &f, double x);

#endif PWLFCN_H