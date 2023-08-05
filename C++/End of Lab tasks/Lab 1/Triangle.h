class Triangle{
    private:
        float XA,XB,XC,YA,YB,YC,AB,AC,BC,A,B,C,Base,Height,Area;
    public:
        Triangle();
        Triangle(float,float,float,float,float,float);
        void SetXA(float);
        void SetXB(float);
        void SetXC(float);
        void SetYA(float);
        void SetYB(float);
        void SetYC(float);
        float getXA();
        float getXB();
        float getXC();
        float getYA();
        float getYB();
        float getYC();
        float getAB();
        float getAC();
        float getBC();
        float getA();
        float getB();
        float getC();
        float getBase();
        float getHeight();
        float getArea();
        bool isIsopleurous();
        bool isIsosceles();
        bool isScalino();
        bool isOrthogonio();
        bool isOxygonio();
        bool isAmvligonio();
};