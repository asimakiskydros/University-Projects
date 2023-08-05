#ifndef Vector_h
#define Vector_h
class Vector{
    private:
        double x,y;
    public:
        Vector();
        Vector(double,double);
        void Setx(double);
        double Getx();
        void Sety(double);
        double Gety();
        double magnitude();
        double angle();
        double angleD();
        void print();
        void multiply(double);
        Vector add(Vector);
};
#endif