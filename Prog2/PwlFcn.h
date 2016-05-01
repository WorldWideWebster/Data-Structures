/*----------PwlFcn.h-------------

by:		Sean Webster
		16.322 Data Structures
		ECE Dept.
		UMASS Lowell

Purpose: provides interface to PwlFcn.cpp

*/
using namespace std;
#ifndef PWLFCN_H
#define PWLFCN_H

const unsigned MaxPts = 10; // Maximum points in a function definition
/*
Type "PwlFucn" represends a piecewise-linear function as a sequence of points
*/

struct PwlFcn
{
	public:
		//Constructor
		PwlFcn() : numPts(0) { }
		//Accessors
		unsigned NumPts() { return numPts; };		// -- Number of points in the function
		Point Pt(unsigned i) { return pt[i]; }		// -- Access point at i
		bool Defined() { return defined; }			// -- List of points defining the function
		//I/O functions
		bool Get(istream &is);
		void Show(ostream &os);
		// Interpolate function
		double Interpolate(double x);
		// Overloaded "+" operator
		PwlFcn operator+(Point p);

		int FcnLength();


/*		bool Empty() { return size == 0; }
		bool Full() { return size >= MaxPts; }
		bool AtEnd() { return current >= size; }
		void Rewind() { current = 0; }
		void Skip() // adcance to next entry
		{
			assert(!AtEnd());
			++current;
		}
		Point CurrentEntry()
		{
			assert(!AtEnd());
			return pt[current];
		}
		*/
	private:
		bool defined;
		unsigned numPts;
		Point pt[MaxPts];
	
		/*unsigned size;
		unsigned current;*/
};

istream & operator>>(istream &is, PwlFcn &f);
ostream & operator<<(ostream &os, PwlFcn &f);


#endif PWLFCN_H