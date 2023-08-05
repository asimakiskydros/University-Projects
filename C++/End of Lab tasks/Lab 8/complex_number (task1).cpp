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
void complex_number::print(){
	if(a==0 && b==0)
		cout<<"0";
	if(a!=0)
		cout<<a;
	if(b>0){
		if(a!=0)
			cout<<"+";
		if(b!=1)
			cout<<b;
		cout<<"i";
	}
	else if(b<0){
		if(b==-1)
			cout<<"-i";
		else
			cout<<b<<"i";			
	}
	cout<<endl;
}