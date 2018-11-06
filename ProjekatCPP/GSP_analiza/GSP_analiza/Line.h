#ifndef _LINE_H_
#define _LINE_H_
#include "Direction.h"
#include "Location.h"
#include <string>
#include <set>
using namespace std;

class Line {
	Direction dirA, dirB;
	string lineNumb, start, destination;
	void loadDirA();
	void loadDirB();

public:
	Line(string, string, string); // constructor
	void loadDir(); // from this method we call loaddirA and loaddirB
	friend ostream& operator<<(ostream&, Line&);
	set<Line*>  linesWithCommonStops(); // return set of lines with common stops with caller
	bool passingTwoStops(int, int); // Checking does line pass 2 stops driving in same direction arguments : stopIDs
	string getLineNumb()const;
	Direction& getDirA();
	Direction& getDirB();
	void setLineNumb(string); // setter for lineNumb
	void addNewStop(); // adding new stop 
	void deleteStop(); // deleting stop
	int getZoneMax(); // get maximum zone caller line passes
	int getNumberOfStops(); // return number of stops
	Stop* closestStop(double, double);
	Line* mostCommonStops(); // method for finding line with most common stops with caller line
};











#endif