#include "binaryGate.h"
#include <string>
using namespace std;

binaryGate::binaryGate():gate(){
	entrance1=entrance2=-1;
}
binaryGate::binaryGate(string desc):gate(desc){
	entrance1=entrance2=-1;
}
int binaryGate::getPins(){
	return 2;
}
void binaryGate::setPin(int entrance,int value){
	if(entrance)
		entrance2=value;
	else
		entrance1=value;
}
int binaryGate::getPin(int entrance){
	return (entrance ? entrance2:entrance1);
}