#include "Location.h"

Location::Location(double xx, double yy){
	x = xx;
	y = yy;
}

double Location::getX(){
	return x;
}

double Location::getY(){
	return y;
}

ostream& operator<<(ostream& os, Location& l){
	return os << "[ " << l.x << " ] [ " << l.y << " ]";
}
