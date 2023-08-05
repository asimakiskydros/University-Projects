#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
using namespace std;

class Student{
	private:
		int AEM;
		char name[30];
		float score;
	public:
		Student();
		friend bool readStudent(char *,Student &);
		friend bool writeToStudent(char *, const Student &);
		friend ostream &operator<<(ostream &,const Student &);
		friend istream &operator>>(istream &,Student &);
		friend bool operator>(const Student &, const Student &); 
};

#endif //STUDENT_H