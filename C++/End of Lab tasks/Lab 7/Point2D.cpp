#include "Point2D.h"
#include <iostream>
using namespace std;

Point2D::Point2D(){ x=y=0; }
Point2D::Point2D(int X,int Y){
	x=X;
	y=Y;
}
bool operator>(const Point2D &obj1,const Point2D &obj2){
	return (obj1.x*obj1.x + obj1.y*obj1.y)>(obj2.x*obj2.x + obj2.y*obj2.y);
}
bool operator<=(const Point2D &obj1, const Point2D &obj2){
	return !(obj1>obj2);
}
ostream &operator<<(ostream &o,const Point2D &obj){
	o<<"("<<obj.x<<","<<obj.y<<")";
	return o;
}