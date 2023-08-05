#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H
#include <iostream>
using namespace std;

class complex_number{
	private:
		double a,b;
	public:
		double getA() const;
		double getB() const;
		void setA(double);
		void setB(double);
		complex_number();
		complex_number(double,double);
		complex_number operator+=(const complex_number &);
		complex_number operator*=(const complex_number &);
		double &operator[](int);
		friend ostream &operator<<(ostream &,const complex_number &);
};
complex_number &operator+(const complex_number &,const complex_number &);
complex_number &operator*(const complex_number &,const complex_number &);
complex_number &operator/(const complex_number &,const complex_number &);

#endif //COMPLEXNUMBER_H