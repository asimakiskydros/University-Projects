#include "Rational.h"
#include <iostream>
using namespace std;

Rational::Rational(){
	numerator=1;
	denominator=1;
}
Rational::Rational(long num, long den){
	numerator=num;
	denominator=den;
	simplify();
}
void Rational::setNumerator(long num){numerator=num;}
void Rational::setDenominator(long den){denominator=den;}
long Rational::getNumerator() const {return numerator;}
long Rational::getDenominator() const {return denominator;}
int Rational::gcd(long num1,long num2){
	long tmp;
	//signs are irrelevant here
	if(num1<0)
		num1*=-1;
	if(num2<0)
		num2*=-1;
	//num1 gotta be the greatest out of the two
	if(num1<num2){
		tmp=num2;
		num2=num1;
		num1=tmp;
	}
	//Pythagorean Method
	while(num2!=0){
		tmp=num2;
		num2=num1%num2;
		num1=tmp;
	}
	return num1;
}
void Rational::simplify(){
	int factor=gcd(numerator,denominator);
	//default all negative signs to the numerator
	if(denominator<0){
		denominator*=-1;
		numerator*=-1;
	}
	if(factor>1){
		numerator/=factor;
		denominator/=factor;
	}
}
Rational Rational::operator=(const Rational &other){
	this->numerator=other.numerator;
	this->denominator=other.denominator;
	return *this;
}
Rational Rational::operator+=(const Rational &other){//a/b + c/d == (ad + bc)/bd
	this->numerator=this->numerator*other.denominator+other.numerator*this->denominator;
	this->denominator*=other.denominator;
	simplify();
	return *this;
}
Rational Rational::operator-=(const Rational &other){//a/b - c/d == (ad - bc)/bd
	this->numerator=this->numerator*other.denominator-other.numerator*this->denominator;
	this->denominator*=other.denominator;
	simplify();
	return *this;
}
Rational Rational::operator*=(const Rational &other){//as expected
	this->numerator*=other.numerator;
	this->denominator*=other.denominator;
	simplify();
	return *this;
}
Rational Rational::operator/=(const Rational &other){//(a / b)/(c / d) == ad / bc
	this->numerator*=other.denominator;
	this->denominator*=other.numerator;
	simplify();
	return *this;
}
Rational Rational::operator*=(long amount){
	this->numerator*=amount;
	simplify();
	return *this;
}
ostream &operator<<(ostream &o, Rational &obj){
	o<<obj.numerator<<"/"<<obj.denominator;
	return o;
}
istream &operator>>(istream &i, Rational &obj){
	i>>obj.numerator>>obj.denominator;
	obj.simplify();
	return i;
}
Rational &operator+(const Rational &obj1, const Rational &obj2){//a/b + c/d == (ad + bc)/bd
	Rational *sum;
	sum=new Rational;
	sum->setNumerator(obj1.getNumerator()*obj2.getDenominator() + obj2.getNumerator()*obj1.getDenominator());
	sum->setDenominator(obj1.getDenominator()*obj2.getDenominator());
	sum->simplify();
	return *sum;
}
Rational &operator-(const Rational &obj1, const Rational &obj2){//a/b - c/d == (ad - bc)/bd
	Rational *sum;
	sum=new Rational;
	sum->setNumerator(obj1.getNumerator()*obj2.getDenominator() - obj1.getDenominator()*obj2.getNumerator());
	sum->setDenominator(obj1.getDenominator()*obj2.getDenominator());
	sum->simplify();
	return *sum;
}
Rational &operator*(const Rational &obj1, const Rational &obj2){//as expected
	Rational *sum;
	sum=new Rational;
	sum->setNumerator(obj1.getNumerator()*obj2.getNumerator());
	sum->setDenominator(obj1.getDenominator()*obj2.getDenominator());
	sum->simplify();
	return *sum;
}
Rational &operator/(const Rational &obj1, const Rational &obj2){//(a / b)/(c / d) == ad / bc
	Rational *sum;
	sum=new Rational;
	sum->setNumerator(obj1.getNumerator()*obj2.getDenominator());
	sum->setDenominator(obj1.getDenominator()*obj2.getNumerator());
	sum->simplify();
	return *sum;
}
bool operator==(const Rational &obj1, const Rational &obj2){
	long comparator1=obj1.getNumerator()*obj2.getDenominator();
	long comparator2=obj1.getDenominator()*obj2.getNumerator();
	//a/b == c/d <=> ad==bc
	return comparator1==comparator2;
}
bool operator!=(const Rational &obj1, const Rational &obj2){
	return !(obj1==obj2);
}
bool operator>(const Rational &obj1, const Rational &obj2){
	long comparator1=obj1.getNumerator()*obj2.getDenominator();
	long comparator2=obj1.getDenominator()*obj2.getNumerator();
	return comparator1>comparator2;
}
bool operator<(const Rational &obj1, const Rational &obj2){
	long comparator1=obj1.getNumerator()*obj2.getDenominator();
	long comparator2=obj1.getDenominator()*obj2.getNumerator();
	return comparator1<comparator2;
}