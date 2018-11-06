#ifndef _FORMAT_H_
#define _FORMAT_H_
#include <map>
#include <set>
using namespace std;

class Format {

public:
	virtual void output(map<string, set<string>>&)=0; // make output file
	virtual ~Format(){}
};


#endif
