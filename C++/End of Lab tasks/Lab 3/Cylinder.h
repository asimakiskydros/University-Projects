#ifndef Cylinder_h
#define Cylinder_h
#include "Sphere.h"
class Cylinder: public Sphere{
    private:
        float l;
    public:
        Cylinder();
        Cylinder(float,float,float,float,float);
        void SetL(float);
        float GetL();
        float Area();
        float Volume();
        bool inCylinder(float,float,float);
};
#endif