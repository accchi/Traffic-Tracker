#include "Direction.h"
#include <iostream>
class Line;


map<int, Stop*>Direction::StopsObjects = { {0,nullptr} }; // initialization for static hashamp

bool Direction::isMade(int stopID){
	auto& iter = StopsObjects.find(stopID);
	if (iter == StopsObjects.end())
		return false;
	return true;
}

list<Stop*>& Direction::getStops(){
	return stops;
}

void Direction::loadStops(string fileName, Line* line ){ // loading all stops for line using regex
	ifstream file(fileName); // ADD CATCH THROW!!!!!
	string s;
	regex reg("([^!]*)!([^!]*)!([^!]*)!([^!]*)!([0-9]).*");
	while (getline(file, s)) {
		smatch result;
		if (regex_match(s, result, reg)) {

			int stopID = atoi(result.str(1).c_str());
			Stop* stop;
			if (!isMade(stopID)) { // We need to check is object for stop already made, if it's made we dont need to make another one we will get it from hashmap
				string stopName = result.str(2);
				double x = atof(result.str(3).c_str());
				double y = atof(result.str(4).c_str());
				int zone = atoi(result.str(5).c_str());
				Location location(x, y);
				stop = new Stop(stopID, stopName, location, zone);
				StopsObjects[stopID] = stop; // add new objects to map
			}
			else { // if we already made it then we will get it from hashmap
				stop = StopsObjects[stopID];
			}
			stop->addLineToSet(line); // add line to set of Lines that are passing this stop
			stops.push_back(stop);

		}
		else {
			std::cout << "No match\n";
		}
	}
	file.close();
}

void Direction::addStop(Line* line){ // adding stop to line, we need ptr to line because we neet to put this line in set 
	int stopID;
	cout << "Unesite sifru stajalista?\n";
	cin >> stopID;
	if (isMade(stopID)) { // if stop with that stopID  exists we just put line in set
		StopsObjects[stopID]->addLineToSet(line);
		stops.push_back(StopsObjects[stopID]); // adding pointer to stop to the list of stops in chosen direction
		cout << "Stajaliste sa sifrom :" << stopID << " je dodato u listu stajalista\n";
	}
	else {
		cout << "Stajaliste sa tom sifrom ne postoji tako da moramo cekati da ga neko sagradi\n";
	}
}

void Direction::deleteStop(Line* l) { //  deleting stop from list of stops
	int stopID;
	cout << "Unesite sifru stajalista?" << endl;
	cin >> stopID;
	auto& it = remove_if(stops.begin(), stops.end(), [stopID](Stop* s)->bool { return stopID == s->getStopID(); }); // removing stop with given stopID
	if (it != stops.end()) { // if it is in list
		StopsObjects[stopID]->removeLineFromSet(l); // remove caller line from allPassingLines for this stop
		stops.erase(it,stops.end());                               // 5.5.2018
		cout << "Stajaliste sa sifrom :" << stopID << " uspesno obrisano\n";
	}
	else { // if it isnt in list
		cout << "Ne postoji stajaliste sa zadatom sifrom\n";
	}
}

Stop * Direction::getStop(int stopID){ // return Stop* for given stopID
	return StopsObjects[stopID];
}

map<int, Stop*>& Direction::getStopsObjects(){
	return StopsObjects;
}

/*Direction::~Direction(){ // destructor for stops DELETEE THIS!!!!!!!! DELETE FROM HASHMAP
	for (Stop*& s : stops) {
		delete s;
	}
	stops.clear(); 
}*/

ostream & operator<<(ostream& os, Direction& dir){ // output operator
	for (Stop* & s : dir.stops) {
		os << *s << endl;
	}
	return os;
}
