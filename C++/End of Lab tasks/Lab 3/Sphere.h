#ifndef Sphere_h
#define Sphere_h
#include "Circle.h"
class Sphere: public Circle{
    protected:
        float z;
    public:
        Sphere();
        Sphere(float,float,float,float);
        void Setz(float);
        float Getz();
        float Area();
        float Volume();
        bool inSphere(float,float,float);
};
#endif