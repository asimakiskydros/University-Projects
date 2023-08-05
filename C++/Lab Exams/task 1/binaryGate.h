#ifndef binarygate_h
#define binarygate_h
#include "gate.h"
#include <string>
using namespace std;

class binaryGate:public gate{
	protected:
		int entrance1,entrance2;
	public:
		binaryGate();
		binaryGate(string);
		int getPins();
		void setPin(int,int);
		int getPin(int);
};

#endif //binarygate_h