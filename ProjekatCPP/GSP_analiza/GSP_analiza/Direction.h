#ifndef _DIRECTION_H_
#define _DIRECTION_H_
#include <list>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include "Stop.h"
using namespace std;
class Line;

class Direction {
	list<Stop*> stops;
	static map<int,Stop*> StopsObjects; // Hash map which will contain all stops objects that I made
	bool isMade(int);
public:
	list<Stop*>& getStops();
	void loadStops(string,Line*);
	friend ostream& operator<<(ostream&, Direction&);
	void addStop(Line*);
	void deleteStop(Line*);
	static Stop* getStop(int);
	static map<int, Stop*>& getStopsObjects();
	//~Direction();
};










#endif