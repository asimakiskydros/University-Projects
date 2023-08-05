#include "myFile.h"
#include <cstring>
#include <fstream>
using namespace std;

myFile::myFile(){
	name=nullptr;
}
myFile::myFile(char* filename){
	name=new char[strlen(filename)+1];
	strcpy(name,filename);
}
void myFile::setName(char *filename){
	if(name!=nullptr)
		delete [] name;
	name=new char[strlen(filename)+1];
	strcpy(name,filename);
}
char *myFile::getName(){
	return name;
}
bool myFile::exists() const{
	ifstream ifs;
	ifs.open(this->name);
	if(ifs.is_open()){
		ifs.close();
		return true;
	}
	else
		return false;
}
int myFile::countLines() const{
	ifstream ifs;
	ifs.open(this->name);
	int count=0;
	char c;
	if(ifs.is_open()){
		while(ifs>>noskipws>>c)
			if(c=='\n')
				count++;
		count++;//the last line with actual text either has endl or it hasn't;
		//either way, EOF counts as a stopgap
		ifs.close();
	}
	return count;
}
int myFile::countChars() const{
	ifstream ifs;
	ifs.open(this->name);
	int count=0;
	char c;
	if(ifs.is_open()){
		while(ifs>>noskipws>>c)
			count++;
		count++;//EOF
		ifs.close();
	}
	return count;
}
myFile myFile::operator=(const myFile &other){
	ofstream ofs;
	ifstream ifs;
	ofs.open(this->name);
	ifs.open(other.name);
	char c;
	if(ofs.is_open() && ifs.is_open())
		while(ifs>>noskipws>>c)
			ofs<<c;
	if(ofs.is_open())
		ofs.close();
	if(ifs.is_open())
		ifs.close();
		return *this;
}
myFile & myFile::operator+=(const myFile &other){
	ofstream ofs;
	ifstream ifs;
	ofs.open(this->name,ios::out | ios::app);
	ifs.open(other.name);
	char c;
	if(ofs.is_open() && ifs.is_open())
		while(ifs>>noskipws>>c)
			ofs<<c;
	if(ofs.is_open())
		ofs.close();
	if(ifs.is_open())
		ifs.close();
		return *this;
}
bool operator==(const myFile &obj1,const myFile &obj2){
	bool equal=true;
	if(!obj1.exists() || !obj2.exists())
		equal=false;
	if(equal && obj1.countLines()!=obj2.countLines())
		equal=false;
	if(equal && obj1.countChars()!=obj2.countChars())
		equal=false;
	if(equal){
		ifstream ifs1,ifs2;
		char c1,c2;
		ifs1.open(obj1.name);
		ifs2.open(obj2.name);
		while(ifs1>>noskipws>>c1 && ifs2>>noskipws>>c2 && equal)
			if(c1!=c2)
				equal=false;
	}
	return equal;
}