#ifndef _STOP_H_
#define _STOP_H_
#include <string>
#include <set>
#include "Location.h"
using namespace std;
class Line;
class Direction;

class Stop {
	int stopID; 
	string name;
	Location location; // x, y location
	int zone; // zone of stop
	set<Line*> lines;
public:
	Stop(int, string, Location,int);
	friend ostream& operator<<(ostream&, Stop&);
	void addLineToSet(Line*);
	void removeLineFromSet(Line*);
	set<Line*>& getLines();
	int getStopID() const;
	int getZone() const;
	set<Line*> allPassingLines(); // getter for lines
	Location& getLocation();
	set<Stop*> oneDriveStops();
	Stop* findNextStop(Direction&);
};







#endif