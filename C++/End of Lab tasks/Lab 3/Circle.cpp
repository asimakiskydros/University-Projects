#include <cmath>
#include "Circle.h"

const double PI=atan(1)*4;

Circle::Circle(){x=y=r=0;}
Circle::Circle(float a,float b,float c){
    x=a;
    y=b;
    r=c;
}
void Circle::Setx(float num){x=num;}
void Circle::Sety(float num){y=num;}
void Circle::SetR(float num){r=num;}
float Circle::Getx(){return x;}
float Circle::Gety(){return y;}
float Circle::GetR(){return r;}
float Circle::Diameter(){return 2*r;}
float Circle::Perimeter(){return 2*PI*r;}
float Circle::Area(){return PI*r*r;}
bool Circle::inCircle(float xA,float yA){return !(sqrt(pow((xA-x),2)+pow((yA-y),2))>r);}
//The above function checks if the distance is larger than the radius
//and returns the opposite bool