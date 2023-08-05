#include "Student.h"
#include <fstream>
#include <iostream>

using namespace std;

Student::Student(){AEM=score=0;}
bool readStudent(char* filename, Student &obj){
	ifstream ifs;
	ifs.open(filename);
	if(ifs.is_open())
		ifs>>obj.AEM>>obj.name>>obj.score;
	else
		return false;
	ifs.close();
	return true;
}
bool writeToStudent(char *filename, const Student &obj){
	ofstream ofs;
	ofs.open(filename);
	if(ofs.is_open())
		ofs<<obj.AEM<<" "<<obj.name<<" "<<obj.score;
	else
		return false;
	ofs.close();
	return true;
}
ostream &operator<<(ostream &o,const Student &obj){
	o<<obj.AEM<<" "<<obj.name<<" "<<obj.score;
	return o;
}
istream &operator>>(istream &i,Student &obj){
	i>>obj.AEM>>obj.name>>obj.score;
	return i;
}
bool operator>(const Student &a, const Student &b){
	if(a.score>b.score)
		return true;
	return false;
}