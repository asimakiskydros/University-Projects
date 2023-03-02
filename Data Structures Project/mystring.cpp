#include "mystring.h"

#include <iostream>
#include <cstring>
using namespace std;

mystring::mystring(){
	data=new char[1];
}
mystring::~mystring(){
	delete [] data;
}
char *mystring::getData(){
	return data;
}
mystring &mystring::fix(){
	int length=strlen(this->data)+1;
	char *temp=new char[length];
	int j=0;
	for(int i=0;i<length;i++){
		if(this->data[i]=='.'
		|| this->data[i]=='!' 
		|| this->data[i]=='?'
		|| this->data[i]==','){
			temp[j++]='\0';
			break;
		}
		else if(this->data[i]>='A' && this->data[i]<='Z')
			temp[j++]=this->data[i] + 32;
		else if((this->data[i]>='a' && this->data[i]<='z')
			|| 	(this->data[i]>='1' && this->data[i]<='9')
			||	 this->data[i]=='\0')
			temp[j++]=this->data[i];
	}
	*this=temp;
	return *this;
}
void mystring::print(const mystring &obj){
	cout<<obj.data;
}
mystring &mystring::operator=(char *string){
	delete [] this->data;
	this->data=new char[strlen(string)+1];
	strcpy(this->data,string);
	return *this;
}
mystring &mystring::operator=(const mystring &obj){
	return *this=obj.data;
}
ostream &operator<<(ostream &o,const mystring &obj){
	o<<obj.data;
	return o;
}
istream &operator>>(istream &i,mystring &obj){
	char string[500];
	i>>string;
	obj=string;
	return i;
}