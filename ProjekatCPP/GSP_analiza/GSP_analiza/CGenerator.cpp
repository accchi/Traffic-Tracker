#include "CGenerator.h"

void CGenerator::generate(Network* n){ // generating C graph
	map<pair<Line*, Line*>, int> map = n->pairsOfLinesWithCommonStops();

	for (auto& it : map) { // iterate map and for every lineNumb put in set lineNumb that have common stops 
		graph[it.first.first->getLineNumb()].insert(it.first.second->getLineNumb()); 
		graph[it.first.second->getLineNumb()].insert(it.first.first->getLineNumb()); // 6.5.2018
	}
}
