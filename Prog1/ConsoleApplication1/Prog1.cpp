/* Arbitrary Periodic Function Generator

by:		Sean Webster
		16.322 Data Structures
		ECE Dept.
		UMASS Lowell

Purpose: demonstrate knowledge of c

*/

#include <iostream>
#include <cmath>
#include "Point.h"
#include "PwlFcn.h"

using namespace std;

int main()
{
	//--------Variable Definitions
	int currPt = 0;	//point counter

	
	PwlFcn pie; //Piecewise linear function

	//---------Getting the points and stuff---------------
	cout << "ENTER A FUNCTION DEFINITION\n\n";
	
	GetF("Enter the next point: ", pie);

	cout << "\nHere is the function definition:\n";
	currPt = 0;

	//------------Draw those points----------------
	while (currPt != pie.numPts)
	{
		ShowPoint(pie.pt[currPt]);
		currPt++;
	}

	//----------Show that pwlfcn-------------
	ShowF(pie);

	system("pause");
}