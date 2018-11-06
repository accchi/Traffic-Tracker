#ifndef _CSVFORMAT_H_
#define _CSVFORMAT_H_
#include "Format.h"

class CSVFormat: virtual public Format {
	void outputID(map<string, set<string>>&); // first way, just 2 node IDs
	void outputList(map<string, set<string>>&); // adjency list
public:
	void output(map<string, set<string>>&); // make output file in CSV format
};


#endif