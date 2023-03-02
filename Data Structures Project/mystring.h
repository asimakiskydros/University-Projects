#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using namespace std;

class mystring{
	private:
		char *data;
	public:
		mystring();
		~mystring();
		mystring & fix();
		char * getData();
		void print(const mystring &);
		mystring &operator=(char *);
		mystring &operator=(const mystring &);
		friend ostream &operator<<(ostream &,const mystring &);
		friend istream &operator>>(istream &,mystring &);
};

#endif //MYSTRING_H