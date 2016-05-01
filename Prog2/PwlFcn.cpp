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

bool PwlFcn::Get(istream &is)
{
	int currPt = 0;
	bool pn = pt[currPt].Get(cin);
	currPt++;
	while (pn == true)
	{
		pn = pt[currPt].Get(cin);
		currPt++;
	}
	numPts = currPt - 1;
	return 1;
}

/*-------------------ShowF-----------------

PURPOSE
-Define function
-Draw the PWLFCN as x and y coordinates

OUTPUT PARAMETERS
SHows function as coordinates

*/

void PwlFcn::Show(ostream &os)
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
	int fcnTime = FcnLength(); //total function time
	int vTime = startt; //time place holder


	cout << "\nHere is the interpolated waveform:\n";

	if (startt < endt)
	{
		do{
			do{
				if (time < pt[vTime].X())
				{
					vTime = endt % fcnTime;
				}
				cout << "(" << time << ", " << Interpolate(vTime) << ")\n";
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
				cout << "(" << time << ", " << Interpolate(vTime) << ")\n";
				time += timePerPoint; //Time runs per interation
				vTime += timePerPoint;
				if (time < endt) //break loop when time = endt
					break;
			} while (vTime >= fcnTime);
			if (vTime < fcnTime)	//Restart the function if the cycle has ended
				vTime = time % fcnTime;
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

double PwlFcn::Interpolate(double x)
{
	int slope; // delta-y over delta-x
	int lastPt; //sort n
	int nextPt; //sort n+1
	double intercept; //y intercept
	int count = 0; //interator, defined outside of for loop for reasons



	for (; count <= numPts; count++)
	{

		lastPt = pt[count].X();
		nextPt = pt[count + 1].X();

		//Sorting algorith to find points function lies between
		if (x > lastPt && x < nextPt)
		{
			slope = (pt[count + 1].Y() - pt[count].Y()) / (pt[count + 1].X() - pt[count].Y());
			intercept = pt[count].Y() - (slope * pt[count].X());
			break;
		}
		else if (x == lastPt || x == nextPt)
		{
			if (x == lastPt)
				intercept = pt[count].Y();
			if (x == nextPt)
				intercept = pt[count + 1].Y();
			slope = 0;
			break;
		}
	}

	return (intercept + (slope * x));

}


PwlFcn PwlFcn::operator+(Point p)
{
	i;
}

int PwlFcn::FcnLength()
{
	return pt[numPts - 1].X() - pt[0].X();
}