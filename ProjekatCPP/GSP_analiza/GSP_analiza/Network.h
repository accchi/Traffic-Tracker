#ifndef _NETWORK_H_
#define _NETWORK_H_
#include <string>
#include <regex>
#include <fstream>
#include <list>
#include <map>
#include "Line.h"
#include "FileException.h"
using namespace std;
class Generator;

class Network {
	list<Line*> lines;
	Generator* generator;

	void filterLinesZone(); // by zone 1; 1,2; 1,2,3;
	void filterLinesLineNumb(); // by LineNumb <,> and > <
	void filterLinesStop(); // filter by number of stops
public:
	void loadLines(string); // method for loading all lines
	void loadCoupleLines(string);// method for loading couple lines
	friend ostream& operator<<(ostream&, Network&); // operator for output
	bool deleteLine(string); // string is for lineNumb ( 25P, EKO1... )
	Line* getLine(string); // getter for single line from list
	bool changeLineNumb(string, string); // string1=oldLineNumb string2=newLineNumb
	void filterLines(); // delete lines with filter that you want
	Stop* closestStop(double,double); // Geo closest stop
	void generate(); // method for choosing type of generator
	Generator* getGenerator(); // getter for generator
	map<pair<Line*, Line*>, int> pairsOfLinesWithCommonStops(int n=-1); // return map with pairs of lines with count how much common stops they have
	void shortestPath(int, int);
	int numberOfTransfers(int, int); // min number of transfers between 2 stops
	~Network();

};



#endif
