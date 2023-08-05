#include <iostream>
#include <string>
#include "gate.h"
#include "binaryGate.h"
#include "andGate.h"
#include "orGate.h"
void print (gate *o)
{
 cout<<o->getLabel()<<" has "<<o->getPins()<<" pins with values "<<o->getPin(0)<<
 " and "<<o->getPin(1)<<" and returns "<<o->getOutput()<<endl;
}
using namespace std;
int main()
{
 gate *b, *g1, *g2;
 string s;
 int i,p;
 cin>>s;
 gate a(s);
 b = new binaryGate();
 cin>>s;
 b ->setLabel(s);
 cin>>s;
 g1 = new andGate(s);
 cin>>s;
 g2 = new orGate(s);
 for (i=0;i<2;i++)
 {
 cin>>p;
 a.setPin(i,p);
 b->setPin(i,p);
 g1->setPin(i,p);
 g2->setPin(i,p);
 }
 print (&a);
 print (b);
 print (g1);
 print (g2);
}