#ifndef orgate_h
#define orgate_h

#include "binaryGate.h"
#include <string>
using namespace std;

class orGate:public binaryGate{
	public:
		orGate();
		orGate(string);
		int getOutput();
};

#endif //orgate_h