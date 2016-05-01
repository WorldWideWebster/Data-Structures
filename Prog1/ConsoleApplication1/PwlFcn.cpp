/*----------PwlFcn.cpp-------------

by:		Sean Webster
		16.322 Data Structures
		ECE Dept.
		UMASS Lowell

Purpose: Defines functions to work on peicewise linear function

*/
#include <iostream>
#include "Point.h"
#include "PwlFcn.h"


using namespace std;
/*
Type "PwlFucn" represends a piecewise-linear function as a sequence of points
*/

/*-------------------GetF-----------------

PURPOSE
Get x and y of a particular point in PWLFCN

OUTPUT PARAMETERS
Point data x and y are gathered and sent to struct

RETURN VALUES
boolean tellign whether point was read
*/

bool GetF(const char *prompt, PwlFcn &f)
{
	int currPt = 0;
	bool pn;
	pn = GetPoint("Enter the first point : ", f.pt[currPt]);
	currPt++;
	while (pn == true)
	{
		pn = GetPoint(prompt, f.pt[currPt]);
		currPt++;
	}
	f.numPts = currPt - 1;
	return 1;
}

/*-------------------ShowF-----------------

PURPOSE
-Define function
-Draw the PWLFCN as x and y coordinates

OUTPUT PARAMETERS
SHows function as coordinates

*/

void ShowF(PwlFcn &f)
{
	int startt; //time start
	int endt; // time end
	int interPoints; //number of interpolated points

	//-----------Getting the info to draw the function-------------------
	cout << "\nWhat is the start time? ";
	cin >> startt;
	cout << endl << "What is the end time? ";
	cin >> endt;
	cout << "\nHow many points? ";
	cin >> interPoints;

	//--------------------Meat and Potatoes of Function----------------------
	int time = startt;	// running time
	int timePerPoint = (endt - startt) / (interPoints - 1);		//time div
	int fcnTime = f.pt[f.numPts - 1].x - f.pt[0].x;	//total function time
	int vTime = startt; //time place holder


	cout << "\nHere is the interpolated waveform:\n";

	if (startt < endt)
	{
		do{
			do{
				if (time < f.pt[vTime].x)
				{
					vTime = endt % fcnTime;
				}
				cout << "(" << time << ", " << Interpolate(f, vTime) << ")\n";
				time += timePerPoint; //Time runs per interation
				vTime += timePerPoint;
				if (time > endt) //break loop when time = endt
					break;
			} while (vTime <= fcnTime);
			if (vTime > fcnTime)	//Restart the function if the cycle has ended
				vTime = startt + timePerPoint;
		} while (time < endt);
	}
	if (startt > endt) //Cases where function is in reverse
	{
		vTime = time % fcnTime;
		do{
			do{
				cout << "(" << time << ", " << Interpolate(f, vTime) << ")\n";
				time += timePerPoint; //Time runs per interation
				vTime += timePerPoint;
				if (time < endt) //break loop when time = endt
					break;
			} while (vTime >= fcnTime);
			if (vTime < fcnTime)	//Restart the function if the cycle has ended
				vTime =  time % fcnTime;
		} while (time >= endt);
	}
}



/*-------------------Interpolate-----------------

PURPOSE
Show y value at given x value of pwlfcn

OUTPUT PARAMETERS
double y value from value at x

RETURN VALUES
double y value


*/

double Interpolate(PwlFcn &f, double x)
{
	int slope; // delta-y over delta-x
	int lastPt; //sort n
	int nextPt; //sort n+1
	double intercept; //y intercept
	int count = 0; //interator, defined outside of for loop for reasons
	


	for (; count <= f.numPts; count++)
	{

		lastPt = f.pt[count].x;	
		nextPt = f.pt[count + 1].x;
		
		//Sorting algorith to find points function lies between
		if (x > lastPt && x < nextPt)
		{
			slope = (f.pt[count + 1].y - f.pt[count].y) / (f.pt[count + 1].x - f.pt[count].x);		
			intercept = f.pt[count].y - (slope * f.pt[count].x);
			break;
		}
		else if (x == lastPt || x == nextPt)
		{
			if (x == lastPt)
				intercept = f.pt[count].y;
			if (x == nextPt)
				intercept = f.pt[count + 1].y;
			slope = 0;
			break;
		}
	}
	
	return (intercept + (slope * x));

}
