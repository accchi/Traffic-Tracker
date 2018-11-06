#include "Stop.h"
#include "Line.h"

Stop::Stop(int id, string nam, Location loc,int z):location(loc){
	stopID = id;
	name = nam;
	zone = z;
}

void Stop::addLineToSet(Line* line){ // add line to set of lines that cross this stop
	lines.insert(line);
}

void Stop::removeLineFromSet(Line * line){
	lines.erase(line);
}

set<Line*>& Stop::getLines(){
	return lines;
}

int Stop::getStopID() const{
	return stopID;
}
int Stop::getZone()const {
	return zone;
}

set<Line*> Stop::allPassingLines(){
	return lines;
}

Location & Stop::getLocation(){
	return location;
}
Stop* Stop::findNextStop(Direction& dir) { // finding next stop in given direction
	auto& it = find_if(dir.getStops().begin(), dir.getStops().end(), [this](Stop* s)->bool { return s->getStopID() == getStopID(); });
	if (it != dir.getStops().end()) {  // if given stop is found in direction
		if (++it != dir.getStops().end()) // find next to it
			return *it;
	}
	return nullptr;
}

set<Stop*> Stop::oneDriveStops(){
	set<Stop*> stops;
	Stop* s;
	for (Line* l : lines) {  // lines- all lines that pass this caller stop
		if (l) {
			s = findNextStop(l->getDirA()); // try to find it in dirA
			if (!s)
				s = findNextStop(l->getDirB()); // not found, try to find it in B
			if (s)  // found, put in set
				stops.insert(s);
		}
	}
	return stops;
}


ostream & operator<<(ostream& os, Stop& s){
	return os << s.stopID << " " << s.name << " " << s.location << " " << s.zone;
}
