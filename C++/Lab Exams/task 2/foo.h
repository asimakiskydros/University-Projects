#ifndef foo_h
#define foo_h

#include <string>
#include <iostream>
using namespace std;

class foo{
	private:
		string label;
		int value;
	public:
		foo(string,int);
		foo &operator+=(int);
		friend foo &operator+(const foo &,const foo &);
		friend ostream &operator<<(ostream &, const foo &);
};

#endif //foo_h