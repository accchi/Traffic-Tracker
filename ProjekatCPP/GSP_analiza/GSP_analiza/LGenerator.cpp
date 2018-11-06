#include "LGenerator.h"

void LGenerator::generate(Network* n){  // generating L graph; unused argument, needed for C graph

	for (auto& stop : Direction::getStopsObjects()) { // iterating map
		if (stop.second == nullptr) continue; // because we initialize map with nullptr
		set<string> stops; // set of stopIDs which have edge with current stop
		stops.clear(); // prepare set for next iteration
		for (auto& s : stop.second->oneDriveStops())
			stops.insert(to_string(s->getStopID())); // put stopID( string ) in set
		graph[to_string(stop.second->getStopID())] = stops; // put it in map
	}
}
