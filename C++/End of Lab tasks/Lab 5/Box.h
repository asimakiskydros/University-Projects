#ifndef BOX_H
#define BOX_H
#include <iostream>
using namespace std;

class Box{
	private:
		float length,width,height;
	public:
		Box();
		Box(float,float,float);
		void setL(float);
		void setW(float);
		void setH(float);
		float getL() const;
		float getW() const;
		float getH() const;
		Box operator =(const Box &);
		Box operator++();
		Box operator++(int);
		Box operator--();
		Box operator--(int);
		Box operator+=(float);
		Box operator-=(float);
		Box operator*=(float);
		Box operator/=(float);
};

Box &operator+(const Box &, const Box &);
Box &operator-(const Box &, const Box &);
Box &operator+(const Box &, float);
Box &operator-(const Box &, float);
Box &operator*(const Box &, float);
Box &operator/(const Box &, float);
bool operator==(const Box &, const Box &);
bool operator!=(const Box &, const Box &);
ostream &operator<<(ostream &, const Box &);

#endif //BOX_H