#include "Sphere.h"
#include <cmath>

const double PI=atan(1)*4;

Sphere::Sphere():Circle(){z=0;}
Sphere::Sphere(float a,float b,float c, float d):Circle(a,b,d){z=c;}
void Sphere::Setz(float num){z=num;}
float Sphere::Getz(){return z;}
float Sphere::Area(){return 4*Circle::Area();}
float Sphere::Volume(){return Area()*r/3;}
bool Sphere::inSphere(float xA,float yA, float zA){
    return !(sqrt(pow((xA-x),2)+pow((yA-y),2)+pow((zA-z),2))>r);
}