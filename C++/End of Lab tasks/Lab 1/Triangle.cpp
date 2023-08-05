#include <cmath>
#include "Triangle.h"
#ifndef M_PI
#define M_PI 3.14159265
#endif //M_PI

Triangle::Triangle(){ XA=XB=XC=YA=YB=YC=0; }
Triangle::Triangle(float a,float b,float c,float d,float e,float f){
    XA=a;
    YA=b;
    XB=c;
    YB=d;
    XC=e;
    YC=f;
}
void Triangle::SetXA(float number){ XA=number; }
void Triangle::SetXB(float number){ XB=number; }
void Triangle::SetXC(float number){ XC=number; }
void Triangle::SetYA(float number){ YA=number; }
void Triangle::SetYB(float number){ YB=number; }
void Triangle::SetYC(float number){ YC=number; }
float Triangle::getXA(){ return XA; }
float Triangle::getXB(){ return XB; }
float Triangle::getXC(){ return XC; }
float Triangle::getYA(){ return YA; }
float Triangle::getYB(){ return YB; }
float Triangle::getYC(){ return YC; }
float Triangle::getAB(){ return sqrt(pow((XA-XB),2)+pow((YA-YB),2)); }
float Triangle::getAC(){ return sqrt(pow((XA-XC),2)+pow((YA-YC),2)); }
float Triangle::getBC(){ return sqrt(pow((XB-XC),2)+pow((YB-YC),2)); }
float Triangle::getA(){
    double cosA=(pow(getAC(),2)+pow(getAB(),2)-pow(getBC(),2))/(2*getAB()*getAC());
    return (float)acos(cosA);
}
float Triangle::getB(){
    double cosB=(pow(getBC(),2)+pow(getAB(),2)-pow(getAC(),2))/(2*getAB()*getBC());
    return (float)acos(cosB);
}
float Triangle::getC(){
    double cosC=(pow(getAC(),2)+pow(getBC(),2)-pow(getAB(),2))/(2*getAC()*getBC());
    return (float)acos(cosC);
}
float Triangle::getBase(){ return getAB(); }
float Triangle::getHeight(){ return sin(getA())*getAC(); }
float Triangle::getArea(){ return getBase()*getHeight()/2; }
bool Triangle::isIsopleurous(){
    float deg_acc=0.0001;
    if(fabs(getAB()-getAC())<deg_acc && fabs(getAB()-getBC())<deg_acc)
        return true;
    return false;
}
bool Triangle::isIsosceles(){
    float deg_acc=0.0001;
    if(fabs(getAB()-getAC())<deg_acc || fabs(getAB()-getBC())<deg_acc || fabs(getAC()-getBC())<deg_acc )
        return true;
    return false;
}
bool Triangle::isScalino(){ return true; }
bool Triangle::isOrthogonio(){
    float deg_acc=0.0001;
    if(fabs(getA()-M_PI/2)<deg_acc || fabs(getB()-M_PI/2)<deg_acc || fabs(getC()-M_PI/2)<deg_acc)
        return true;
    return false;
}
bool Triangle::isOxygonio(){
    if(getA()<M_PI/2  && getB()<M_PI/2 && getC()<M_PI/2)
        return true;
    return false;
}
bool Triangle::isAmvligonio(){ return true; }