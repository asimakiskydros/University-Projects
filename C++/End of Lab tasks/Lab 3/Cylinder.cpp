#include <cmath>
#include "Cylinder.h"

const double PI=atan(1)*4;

Cylinder::Cylinder():Sphere(){l=0;}
Cylinder::Cylinder(float a,float b, float c, float d, float e):Sphere(a,b,c,d){l=e;}
void Cylinder::SetL(float num){l=num;}
float Cylinder::GetL(){return l;}
float Cylinder::Area(){return Perimeter()*(r+l);}
float Cylinder::Volume(){return Circle::Area()*l;}
bool Cylinder::inCylinder(float xA,float yA,float zA){
    if(!inCircle(xA,yA) || zA>(z+l/2) || zA<(z-l/2))
        return false;
    return true;
}