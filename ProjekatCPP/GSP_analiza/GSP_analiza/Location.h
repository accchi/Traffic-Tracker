#ifndef _LOCATION_H_
#define _LOCATION_H_
#include <iostream>
using namespace std;

class Location {
	double x, y;
public:
	Location(double, double);
	friend ostream& operator<<(ostream&, Location&);
	double getX();
	double getY();
};








#endif
