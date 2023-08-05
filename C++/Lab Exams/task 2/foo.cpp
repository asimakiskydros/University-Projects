#include "foo.h"
#include <string>
using namespace std;

foo::foo(string desc, int initializer){
	label=desc;
	value=initializer;
}
foo &foo::operator+=(int number){
	this->value+=number;
	return *this;
}
foo &operator+(const foo &obj1, const foo& obj2){
	string newlabel=obj1.label+obj2.label;
	foo* temp=new foo(newlabel,obj1.value+obj2.value);
	return *temp;
}
ostream &operator<<(ostream &o, const foo& obj){
	o<<obj.label<<", "<<obj.value;
	return o;
}