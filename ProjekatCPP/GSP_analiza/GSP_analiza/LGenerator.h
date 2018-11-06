#ifndef _LGENERATOR_H_
#define _LGENERATOR_H_
#include "Generator.h"

class LGenerator : virtual public Generator {

public:
	void generate(Network*);
};



#endif
