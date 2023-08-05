#include "gate.h"
#include <string>
using namespace std;

gate::gate(){
	label=string();
}
gate::gate(string description){
	label=description;
}
void gate::setLabel(string description){
	label=description;
}
string gate::getLabel(){
	return label;
}
int gate::getOutput(){
	return -1;
}
int gate::getPins(){
	return 0;
}
void gate::setPin(int arg1,int arg2){}
int gate::getPin(int arg){
	return -1;
}