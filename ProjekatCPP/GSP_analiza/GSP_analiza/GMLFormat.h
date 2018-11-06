#ifndef _GMLFORMAT_H_
#define _GMLFORMAT_H_
#include "Format.h"

class GMLFormat: virtual public Format {
public:
	void output(map<string, set<string>>&); // make output file in GML format
};



#endif
