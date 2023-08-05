#include "andGate.h"

andGate::andGate():binaryGate(){}
andGate::andGate(string desc):binaryGate(desc){}
int andGate::getOutput(){
	if(entrance1==1 && entrance2==1)
		return 1;
	return 0;
}