#ifndef _GENERATOR_H_
#define _GENERATOR_H_
#include "Network.h"
#include <map>
#include <set>
class Format;

class Generator {
protected:
	map<string, set<string>> graph; // map simulate graph
	Format* format; // format for output 
public:
	virtual void generate(Network*) = 0; // abstract method  for graph generating
	void generateFiles(); // choosing format for making file and calling output function
	virtual ~Generator();
};










#endif
