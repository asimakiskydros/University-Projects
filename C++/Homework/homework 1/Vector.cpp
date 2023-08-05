#include "Vector.h"
#include <cmath>
#include <iostream>

using namespace std;
const float PI=atan(1)*4;

Vector::Vector(){x=y=0;}
Vector::Vector(double X, double Y){
    x=X;
    y=Y;
}
void Vector::Setx(double num){x=num;}
void Vector::Sety(double num){y=num;}
double Vector::Getx(){return x;}
double Vector::Gety(){return y;}
double Vector::magnitude(){return sqrt(x*x+y*y);}
double Vector::angle(){return atan((double)y/x);}
double Vector::angleD(){return angle()*180/PI;}
void Vector::print(){
    double temp;
    cout<<"("<<x<<","<<y<<")"<<endl;
    temp=magnitude();
    cout<<temp<<endl;
    temp=angleD();
    cout<<temp<<endl;
}
void Vector::multiply(double f){
    Setx(f*x);
    Sety(f*y);
}
Vector Vector::add(Vector other){
    Vector temp;
    temp.x=x+other.x;
    temp.y=y+other.y;
    return temp;
}