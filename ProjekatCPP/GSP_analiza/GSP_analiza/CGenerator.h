#ifndef _CGENERATOR_H_
#define _CGENERATOR_H_
#include "Generator.h"

class CGenerator: virtual public Generator {

public:
	void generate(Network*);
};



#endif
