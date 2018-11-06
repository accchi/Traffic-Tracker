#include "GMLFormat.h"
#include <fstream>
#include <string>
using namespace std;

void GMLFormat::output(map<string, set<string>>& graph){
	ofstream file;
	file.open("izlazGML.txt");
	file << "graph\n" <<"[\n";
	for (auto& g : graph) { // print nodes
		file << "node\n[\nid " << g.first << endl << "label \"" << g.first << "\"\n]\n";
	}
	for (auto& g : graph) { // print edges 
		for (auto& gg : g.second) { // iterate set
			file << "edge\n[\nsource " << g.first << "\ntarget " << gg << "\nlabel \"Edge " << g.first << " to " << gg << "\"\n]\n";
		}
	}
	file << "]";
	file.close();

}
