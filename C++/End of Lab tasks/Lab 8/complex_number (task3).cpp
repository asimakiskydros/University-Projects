#include "complex_number.h"
#include <iostream>
using namespace std;

complex_number::complex_number(){
	a=b=1;
}
complex_number::complex_number(double v1, double v2){
	a=v1;
	b=v2;
}
void complex_number::setA(double value){
	a=value;
}
void complex_number::setB(double value){
	b=value;
}
double complex_number::getA() const{
	return a;
}
double complex_number::getB() const{
	return b;
}
ostream &operator<<(ostream &o,const complex_number &obj){
	if(obj.a==0 && obj.b==0)
		o<<"0";
	if(obj.a!=0)
		o<<obj.a;
	if(obj.b>0){
		if(obj.a!=0)
			o<<"+";
		if(obj.b!=1)
			o<<obj.b;
		o<<"i";
	}
	else if(obj.b<0){
		if(obj.b==-1)
			o<<"-i";
		else
			o<<obj.b<<"i";			
	}
	return o;
}
complex_number &operator+(const complex_number &obj1, const complex_number &obj2){
	complex_number* newobj=new complex_number;
	newobj->setA(obj1.getA()+obj2.getA());
	newobj->setB(obj1.getB()+obj2.getB());
	return *newobj;
}
complex_number &operator*(const complex_number &obj1, const complex_number &obj2){
	complex_number* newobj=new complex_number;
	newobj->setA(obj1.getA()*obj2.getA()-obj1.getB()*obj2.getB());
	newobj->setB(obj1.getA()*obj2.getB()+obj1.getB()*obj2.getA());
	return *newobj;
}
complex_number complex_number::operator+=(const complex_number &other){
	*this=*this+other;
	return *this;
}
complex_number complex_number::operator*=(const complex_number &other){
	*this=*this*other;
	return *this;
}