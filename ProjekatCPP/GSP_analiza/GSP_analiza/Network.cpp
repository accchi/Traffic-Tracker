#include "Network.h"
#include <iostream>
#include "LGenerator.h"
#include "CGenerator.h"
#include <queue>
#include <vector>
using namespace std;

void Network::loadLines(string fileName){
	ifstream file(fileName);
	string s;
	regex reg("([^\!]*)!([^\!]*)!([^\!]*)!");
	if (!file.is_open()) throw new FileException(); // if file is not open
	while (getline(file, s)) {
		smatch result;
		if (regex_match(s, result, reg)) {
			string lineNumb = result.str(1);
			string start = result.str(2);
			string destination = result.str(3);

			Line* line=new  Line(lineNumb, start, destination); //dynamic allocation for every line
			line->loadDir(); // call public method for loading stops, in that method we will call private methods for loading in both directions
			lines.push_back(line);
		}
		else {
			cout << "No match\n" << endl;
		}
	}
	cout << "Sve linije su ucitane\n";
	file.close();
}

void Network::loadCoupleLines(string fileName) {
	cout << "Unesite oznake linija koje zelite da budu ucitane? [ X - za kraj ]\n";
	string s; cin >> s;
	set<string> set;
	while (s != "X") { // inserting all lineNumb that are needed to be loaded
		set.insert(s);
		cin >> s;
	}
	ifstream file(fileName);
	regex reg("([^\!]*)!([^\!]*)!([^\!]*)!");
	if (!file.is_open()) throw new FileException(); // if file is not open
	cout << "Linije: ";
	while (getline(file, s)) {
		smatch result;
		if (regex_match(s, result, reg)) {
			string lineNumb = result.str(1);
			if (set.find(lineNumb) == set.end()) // if lineNumb is not in set then continue
				continue;
			cout << " |" << lineNumb << "| "; // print lines that are loaded
			string start = result.str(2);
			string destination = result.str(3);

			Line* line = new  Line(lineNumb, start, destination); //dynamic allocation for every line
			line->loadDir(); // call public method for loading stops, in that method we will call private methods for loading in both directions
			lines.push_back(line);
		}
		else {
			cout << "No match\n" << endl;
		}
	}
	cout << " su ucitane\n";
	file.close();
}



Line * Network::getLine(string lineNumb){ //getter for single line with given lineNumb
	auto& it = find_if(lines.begin(), lines.end(), [lineNumb](Line* l)->bool {return lineNumb==l->getLineNumb(); });
	if (it != lines.end())
		return  *it; // returns Line that i found
	else
		return nullptr; // Line not found
}

bool Network::changeLineNumb(string oldLineNumb, string newLineNumb){  
	Line* l = getLine(oldLineNumb);
	if (!l) return false; // line with that line numb doesnt exist
	l->setLineNumb(newLineNumb); // set new lineNumb
	return true;
}


void Network::filterLinesZone() { // filter by zone NEEED TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	cout << "Unesite zonu do koje zelite da budu prikazane linije? [ 1-prva zona; 2-prva i druga zona; 3-prva, druga i treca zona ]\n";
	int zone;
	cin >> zone;
	for (auto& it = lines.begin(); it != lines.end();)
		if ((*it)->getZoneMax() > zone) {
			auto& tmp = it++;
			deleteLine(((*tmp)->getLineNumb()));
		}
		else
			it++;
	/*for (auto& a : lines) // 5.5.2018. PROMENJENOOOOOO TAAAAAAAAAAAD   OLD ONE BUG BUG BUG
		if (a->getZoneMax() > zone)
			deleteLine(a->getLineNumb());
			//lines.remove(a);*/
}

void Network::filterLinesLineNumb() { // filter by line numb
	cout << "[1] Sve manje od zadatog broja linije\n[2] Sve vece od zadatog broja linije\n[3] Sve u zadatom opsegu\n";
	int option, numb,up,down;
	cin >> option;
	switch (option){
	case 1: case 2:cout << "Unesite broj linije?\n";  cin >> numb;
	/*	for_each(lines.begin(), lines.end(), [this, option, numb](Line* l) { // iterating lines        OLD ONE, BUG BUG BUG
			string s = l->getLineNumb();
			regex reg("[^0-9]*([0-9].*)");
			smatch result;
			if (regex_match(s, result, reg)) { // parse integers from string ( EKO1 -> 1... )
				int stopID = atoi(result.str(1).c_str());
				if (option-1?numb > stopID:numb<stopID) deleteLine(s); // delete line if lineNumb is less or greather than numb
			}
		});*/
		for (auto& it = lines.begin(); it != lines.end();) {                      //  5.5.2018
			string s = (*it)->getLineNumb();
			regex reg("[^0-9]*([0-9].*)");
			smatch result;
			if (regex_match(s, result, reg)) { // parse integers from string ( EKO1 -> 1... )
				int stopID = atoi(result.str(1).c_str());
				if (option - 1 ? numb > stopID:numb < stopID) {
					auto& tmp = it++; // if we need to delete elem we need to do it++ because we will remove it
					deleteLine(((*tmp)->getLineNumb()));
				}
				else
					it++;
			}
		}
		break;
	case 3:cout << "Unesite opseg?\n"; cin >> down; cin >> up;
		/*for_each(lines.begin(), lines.end(), [this,down,up](Line* l) { //iterating lines          OLD ONE, BUG BUG BUG
			string s = l->getLineNumb();
			regex reg("[^0-9]*([0-9].*)");
			smatch result;
			if (regex_match(s, result, reg)) { //parse integers from string
				int stopID = atoi(result.str(1).c_str());
				if (up < stopID || stopID < down) deleteLine(s); // delete line out of range
			}
		});*/
		for (auto& it = lines.begin(); it != lines.end();) {                      //  5.5.2018
			string s = (*it)->getLineNumb();
			regex reg("[^0-9]*([0-9].*)");
			smatch result;
			if (regex_match(s, result, reg)) { //parse integers from string
				int stopID = atoi(result.str(1).c_str());
				if (up < stopID || stopID < down) {
					auto& tmp = it++; // if we need to delete elem we need to do it++ because we will remove it
					deleteLine(((*tmp)->getLineNumb()));
				}
				else
					it++;
			}
		}
		break;
	}
}
	
void Network::filterLinesStop() { // filter by number of stops in both directions need TEEEEEEEEEEEEEEESTTTTTTTTTT
	cout << "[1] Sve koje imaju vise od zadatog broja stajalista\n[2] Sve koje imaju manje od zadatog broja stajalista\n";
	int option, numb;
	cin >> option;
	cout << "Unesite broj stajalista?\n";
	cin >> numb;
	/*for (auto& a : lines) {                                      OLD ONE BUG BUG BUG
		switch (option) {
		case 1: if (a->getNumberOfStops() < numb) deleteLine(a->getLineNumb()); break;
		case 2: if (a->getNumberOfStops() > numb) deleteLine(a->getLineNumb()); break;
		}
	}*/
	for (auto& it = lines.begin(); it != lines.end();) {
		switch (option) {
		case 1: 
			if ((*it)->getNumberOfStops() < numb) {
			auto& tmp = it++;
			deleteLine((*tmp)->getLineNumb());
			}
			else it++;
			break;
		case 2: 
			if ((*it)->getNumberOfStops() > numb) {
				auto& tmp = it++;
				deleteLine((*tmp)->getLineNumb());
			}
			else it++;
			break;
		}
	}
}
void Network::filterLines(){ // wrapper method for all filters
	int option;
	cout << "[1] Na osnovu zone\n[2] Na osnovu oznake\n[3] Na osnovu broja stajalista\n"; cin >> option;
	switch (option) {
	case 1: filterLinesZone(); break;
	case 2: filterLinesLineNumb(); break;
	case 3: filterLinesStop(); break;
	}
}
Stop* Network::closestStop(double x, double y){ // wrapper function for closest stop
	double min = INT_MAX;
	Stop* stop = nullptr;
	for (auto& l : lines) {
		Stop* s = l->closestStop(x, y);
		if (!s)continue;
		double distance = sqrt(pow(x - s->getLocation().getX(), 2) + pow(y - s->getLocation().getY(), 2));
		if (distance<min) {
				min = distance;
				stop = s;
			}
		}
	return stop;
}

void Network::generate(){ // wrapper for graph generating
	if (generator) delete generator; // if generator already exist then delete it
	cout << "Koju vrstu grafa zelite da generisete?\n[1] L Graf\n[2] C Graf\n"; int option;
	cin >> option; // chose type of generator
	switch (option) {
	case 1: generator = new LGenerator(); break;
	case 2: generator = new CGenerator(); break;
	}
	generator->generate(this); // generate graph; this needed for C graph
	cout << "Graf formiran\n";
}

Generator * Network::getGenerator() {
	return generator;
}

map<pair<Line*, Line*>, int> Network::pairsOfLinesWithCommonStops(int n){
	map<pair<Line*, Line*>, int> map;

	for (auto& st : Direction::getStopsObjects()) { // iterate all stops
		if (st.second == nullptr)continue; // because we initialize 0st element of static map with nullptr
		for (Line* l1 : st.second->allPassingLines()) { // iterate all passing lines
			for (Line* l2 : st.second->allPassingLines()) { // iterate all pasing lines
				if (l1->getLineNumb() >= l2->getLineNumb()) continue; // make just 1 pair; example 6,7 and 7,6, make just 6,7
				pair<Line*, Line*> pair = make_pair(l1, l2);
				if (map.find(pair) != map.end())
					map[pair] += 1; // if pair already exist, just increment
				else
					map[pair] = 1; // else initialize it
			}
		}
	}
	if (n > 0) { // deleting all that have lower numb of common stops than n
		for (auto iter = map.begin(); iter != map.end(); ) {
			if (iter->second < n) iter = map.erase(iter);
			else iter++;
		}
	}
	return map;
}

void Network::shortestPath(int id1, int id2) {
	Stop* src = Direction::getStop(id1), *dst = Direction::getStop(id2); // get source and destination stop
	if (!src || !dst) {
		cout << "Ne postoji src ili dst!\n";
		return; // return empty vector if there is no path
	}
	map<Stop*, bool> visited;  // map for saving visited nodes
	map<Stop*, vector<Stop*>> path;
	map<Stop*, vector<Line*>> lines;
	queue<Stop*> que; // queue for BST search
	int flag = 0; // if i found path
	que.push(src);
	visited[src] = 1;
	while (!que.empty()) {
		Stop* next = que.front(); // take next
		que.pop(); // pop it from queue
		set<Stop*> closest = next->oneDriveStops(); // get all stops - distance 1 stop
		for (auto& st : closest) { // iterate oneDriveStops
			if (st == dst) { // if path is found
				path[st] = path[next]; // copy path of ancestor
				path[st].push_back(next); // put ancestor in the path
				path[st].push_back(st); // push back destination
				flag = 1; // found
			}
			if (flag) break; // path is found
			auto iter = visited.find(st); // check if already visited
			if (iter == visited.end()) { // if not visited, visit it and put it in queue
				path[st] = path[next]; // copy path of ancestor
				path[st].push_back(next); // put ancestor in the path
				visited[st] = 1; // flag visited
				que.push(st); // push it back
			}
		}
	}
	auto it = path[dst].begin();
	while(it!=path[dst].end()) {
		if ((it+1)==path[dst].end())
			break;
		for (auto& it1 : (*it)->allPassingLines()) {
			if ((it+1)!=path[dst].end() && it1->passingTwoStops((*it)->getStopID(), (*(1+it))->getStopID())) {
				cout << it1->getLineNumb() << endl;
				break;
			}
		}
		it++;
	}
	if (path[dst].empty())
		cout << "Ne postoji put izmedju dva stajalista!\n";
	else
		for (auto& it : path[dst]) {
			cout << *it << endl;
		}
}

int Network::numberOfTransfers(int id1, int id2) {
	Stop* src = Direction::getStop(id1), *dst = Direction::getStop(id2); // get source and destination stop
	if (!src || !dst)
		return -1; // return empty vector if there is no path
	map<Line*, bool> visited;  // map for saving visited nodes
	queue<Line*> que; // queue for search
	set<Line*>& lines = dst->allPassingLines();
	int numb = 0;
	for (auto& l : src->allPassingLines()) {
		que.push(l);
	}
	que.push(nullptr);
	while (!que.empty()) {
		Line* l = que.front(); // take next
		que.pop();
		if (l == nullptr) { // increase numb of transfers
			numb++;
			if (que.empty()) break;
			l = que.front(); // take next
			que.pop();
			que.push(nullptr);
		}
		visited[l] = 1;
		if (lines.find(l) != lines.end()) { // found
			//cout << "Do cilja smo dosli linijom " << l->getLineNumb() << endl;
			return numb;
		}
		for (Line* line : l->linesWithCommonStops()) {
			if (!visited[line]) {
				que.push(line);
			}
		}
	}
	return -1; // if path between two stops doesnt exist*/
}



bool Network::deleteLine(string lineNumb) { // 21.4.2018.
	Line* l = getLine(lineNumb);
	if (!l) return false; // there is no line with this lineNumb
	int dir = 1;
	do {
		for (auto& stop : dir ? l->getDirA().getStops() : l->getDirB().getStops()) { // get all stops for direction
			stop->getLines().erase(l);
		}
		dir--;
	} while (dir >= 0);
	
	l->getDirA().getStops().clear(); // clear lists of stops in both directions
	l->getDirB().getStops().clear();
	lines.remove(l); // remove Elem from list that contains given pointer   
	//auto& it=lines.erase(find(lines.begin(),lines.end(),l));                    5.5.2018
	if(l)delete l; 
	return true;
}

Network::~Network(){ //destructor for network
	for (Line*& l : lines) {  // free list of pointers
		delete l;
	}
	lines.clear(); // clear list
	for (auto& it : Direction::getStopsObjects()) // free static  map for objects
		delete it.second;
	Direction::getStopsObjects().clear(); // clear map
}

ostream& operator<<(ostream& os, Network& net){
	for (Line *l : net.lines) {
			os << *l;
	}
	return os;
}
