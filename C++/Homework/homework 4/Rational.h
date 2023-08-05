#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
using namespace std;
class Rational{
	private:
		long numerator,denominator;
		int gcd(long,long);//Greatest Common Denominator
	public:
		Rational();
		Rational(long,long);
		void simplify();//eg. 4/8 ----> 1/2
		Rational operator=(const Rational &);
		Rational operator+=(const Rational &);
		Rational operator-=(const Rational &);
		Rational operator*=(const Rational &);
		Rational operator/=(const Rational &);
		Rational operator*=(long);
		void setNumerator(long);
		void setDenominator(long);
		long getNumerator() const;
		long getDenominator() const;
		friend ostream &operator<<(ostream &, Rational &);
		friend istream &operator>>(istream &, Rational &);

};
	Rational &operator+(const Rational &, const Rational &);
	Rational &operator-(const Rational &, const Rational &);
	Rational &operator*(const Rational &, const Rational &);
	Rational &operator/(const Rational &, const Rational &);
	bool operator==(const Rational &, const Rational &);
	bool operator!=(const Rational &, const Rational &);				
	bool operator>(const Rational &, const Rational &);
	bool operator<(const Rational &, const Rational &);
	
#endif //RATIONAL_H