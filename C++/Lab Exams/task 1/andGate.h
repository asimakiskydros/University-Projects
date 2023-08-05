#ifndef andgate_h
#define andgate_h

#include "binaryGate.h"
#include <string>
using namespace std;

class andGate:public binaryGate{
	public:
		andGate();
		andGate(string);
		int getOutput();
};

#endif //andgate_h