#include "orGate.h"

orGate::orGate():binaryGate(){}
orGate::orGate(string desc):binaryGate(desc){}
int orGate::getOutput(){
	if(entrance1==0 && entrance2==0)
		return 0;
	return 1;
}