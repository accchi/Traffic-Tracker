#ifndef _FILEEXCEPTION_H_
#define _FILEEXCEPTION_H_
#include <iostream>
using namespace std;


class FileException {
public:
	friend ostream& operator<<(ostream& os, FileException& f) {
		os << "Fajl Greska!\n";
		return os;
	}


};












#endif
