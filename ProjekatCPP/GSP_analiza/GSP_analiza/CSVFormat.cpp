#include "CSVFormat.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void CSVFormat::outputID(map<string, set<string>>& graph){
	ofstream file;
	file.open("izlazCSVid.txt"); 
	for (auto& it1 : graph) { // iterating graph
		for (auto& it2 : it1.second) { // iterating set
			file << it1.first << ";" << it2 << endl; // a;b etc
		}
	}
	file.close();
}

void CSVFormat::outputList(map<string, set<string>>& graph){ // output like a;b;c;d, adjency list
	ofstream file;
	file.open("izlazCSVlist.txt");
	for (auto& it1 : graph) { // iterating graph
		file << it1.first; //a
		for (auto& it2 : it1.second) { // iterating set
			file << ";" << it2; // a;b;c;d;e
		}
		file << endl; // start with another list
	}
	file.close();
}


void CSVFormat::output(map<string, set<string>>& graph){
	cout << "[1] Dva cvora koja su povezana u jednom redu\n[2] Pomocu liste susednosti\n"; int opt;
	cin >> opt;
	switch (opt) {
	case 1: outputID(graph); break;
	case 2: outputList(graph); break;
	}
}
