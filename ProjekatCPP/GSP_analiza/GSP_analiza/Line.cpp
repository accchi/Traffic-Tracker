#include "Line.h"





Line::Line(string nmb, string st, string des) { // constructor for Line
	lineNumb = nmb;
	start = st;
	destination = des;
}


void Line::loadDirA(){
	dirA.loadStops(lineNumb+"_dirA.txt",this); // loading stops for direction A, this is because i need to add line to set of lines of one stop
}

void Line::loadDirB(){
	dirB.loadStops(lineNumb+"_dirB.txt",this); // loading stops for direction B
}
void Line::loadDir(){ // calling separate functions for loading both directions
	loadDirA();
	loadDirB();
}

set<Line*> Line::linesWithCommonStops(){ //return lines that have common stops with caller line
	set<Line*> common; // init set
	int dir = 1;
	do {
		for (auto& stop : dir ? dirA.getStops() : dirB.getStops()) { // get all stops for direction
			for (auto l : stop->getLines()) { // getter for pointers to all lines that cpass this stop
				if (common.find(l) == common.end())
					common.insert(l);
			}
		}
		dir--;
	} while (dir >= 0);
	
	return common;
}

bool Line::passingTwoStops(int stopID1, int stopID2){
	int dir = 1;
	do {
		int check = 2; // initialize with 2, do -- every time we pass one of stopID in one direction
		for (auto& stop : dir ? dirA.getStops() : dirB.getStops()) { // get all stops for direction
			if (stopID1 == stop->getStopID() || stopID2 == stop->getStopID()) // assume that we wont pass same stop 2 times in same dir
				check--;
		}
		if (!check)
			return true;
		dir--;
	} while (dir >= 0);

	return false;
}

string Line::getLineNumb()const{
	return lineNumb;
}

Direction & Line::getDirA(){
	return dirA;
}

Direction & Line::getDirB(){
	return dirB;
}

void Line::setLineNumb(string newLineNumb){
	lineNumb = newLineNumb;
}

void Line::addNewStop(){
	char dir;
	cout << "Izaberite smer? [ A ili B ]"<<endl; // choosing a direction
	cin >> dir;
	dir == 'A' ? dirA.addStop(this) : dirB.addStop(this);
}

void Line::deleteStop(){ // deleting stops from chosen direction
	char dir;
	cout << "Izaberite smer? [ A ili B ]" << endl; // choosing a direction/ assuming we will always cin a or b
	cin >> dir;
	dir == 'A' ? dirA.deleteStop(this) : dirB.deleteStop(this); // this- need to know the caller line
}

int Line::getZoneMax(){ // returns max zone this line passes
	int zone = 0; // initialize zone, return value 0 means that this line doesnt have any stop
	int dir = 1;
	do {
		for (auto& stop : dir ? dirA.getStops() : dirB.getStops()) { // get all stops for direction
			if (zone < stop->getZone()) // if we find any higher zone
				zone = stop->getZone(); 
		}
		dir--;
	} while (dir >= 0);
	return zone;
}

int Line::getNumberOfStops(){
	int count = 0;
	int dir = 1;
	do {
		for (auto& stop : dir ? dirA.getStops() : dirB.getStops()) // get all stops for direction
			count++; // number of stops ++
		dir--;
	} while (dir >= 0);
	return count; // return number of stops
}

Stop* Line::closestStop(double x, double y){
	int dir = 1;
	double min = INT_MAX;
	Stop* stop = nullptr;
	do {
		for (auto& s : dir ? getDirA().getStops() : getDirB().getStops()) { // get all stops for direction
			double distance = sqrt(pow(x - s->getLocation().getX(), 2) + pow(y - s->getLocation().getY(), 2));
			if (distance<min) {
				min = distance;
				stop = s;
			}
		}
		dir--;
	} while (dir >= 0);
	return stop;
}

Line * Line::mostCommonStops() { // findig line with most common stops
	map<Line*, int> m;
	int dir = 1;
	do {
		for (auto& st : dir ? dirA.getStops() : dirB.getStops()) {
			for (Line* l : st->allPassingLines()) {
				if (l->getLineNumb() == lineNumb) continue; // caller line passes that stop too, need to skip that
				if (m.find(l) != m.end()) { // if line doesnt exist in map
					m[l] = m[l] + 1; 
				}
				else { // initialize doesnt exist in map then initialize it
					m[l] = 1;
				}
			}
		}
		dir--;
	} while (dir >= 0);
	int max = INT_MIN;
	Line* line = nullptr;
	for (auto& iter = m.begin(); iter != m.end(); iter++) { // findig line with most common stops
		if (iter->second > max) {
			max = iter->second;
			line = iter->first;
		}
	}
	return line;
}

ostream & operator<<(ostream& os, Line& l){
	os << l.lineNumb << " " << l.start << " " << l.destination << "\n"; // output basic line informations
	os << "direction A\n" << l.dirA << "\ndirection B\n" << l.dirB << "\n"; // output informations about stops in both directions
	return os;
}
