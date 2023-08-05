#ifndef Circle_h
#define Circle_h
class Circle{
    protected:
        float x,y,r;
    public:
        Circle();
        Circle(float,float,float);
        void Setx(float);
        void Sety(float);
        void SetR(float);
        float Getx();
        float Gety();
        float GetR();
        float Diameter();
        float Perimeter();
        float Area();
        bool inCircle(float,float);
};
#endif