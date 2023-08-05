#ifndef POINT2D_H
#define POINT2D_H
#include <iostream>
using namespace std;

class Point2D{
	private:
		int x,y;
	public:
		Point2D();
		Point2D(int,int);
		friend bool operator>(const Point2D &,const Point2D &);
		friend bool operator<=(const Point2D &,const Point2D &);
		friend ostream &operator<<(ostream &,const Point2D &);
};

#endif //POINT2D_H