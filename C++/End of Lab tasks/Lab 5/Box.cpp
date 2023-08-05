#include "Box.h"
#include <iostream>
#include <cmath>
using namespace std;

Box::Box(){
	length=width=height=0;
}
Box::Box(float l,float w,float h){
	length=l;
	width=w;
	height=h;
}
void Box::setL(float num){
	length=num;
}
void Box::setW(float num){
	width=num;
}
void Box::setH(float num){
	height=num;
}
float Box::getL() const{
	return length;
}
float Box::getW() const{
	return width;
}
float Box::getH() const{
	return height;
}
Box Box::operator =(const Box &other){
	this->length=other.length;
	this->width=other.width;
	this->height=other.height;
	return *this;
}
Box Box::operator++(){
	this->length++;
	this->width++;
	this->height++;
	return *this;
}
Box Box::operator++(int dummy){
	Box r=*this;
	this->length++;
	this->width++;
	this->height++;
	return r;
}
Box Box::operator--(){
	this->length--;
	this->width--;
	this->height--;
	return *this;
}
Box Box::operator--(int dummy){
	Box r=*this;
	this->length--;
	this->width--;
	this->height--;
	return r;
}
Box Box::operator+=(float num){
	this->length+=num;
	this->width+=num;
	this->height+=num;
	return *this;
}
Box Box::operator-=(float num){
	this->length-=num;
	this->width-=num;
	this->height-=num;
	return *this;
}
Box Box::operator*=(float num){
	this->length*=num;
	this->width*=num;
	this->height*=num;
	return *this;
}
Box Box::operator/=(float num){
	this->length/=num;
	this->width/=num;
	this->height/=num;
	return *this;
}
Box &operator+(const Box &obj1, const Box &obj2){
	Box *newObj=new Box;
	newObj->setH(obj1.getH()+obj2.getH());
	newObj->setL(obj1.getL()+obj2.getL());
	newObj->setW(obj1.getW()+obj2.getW());
	return *newObj;
}
Box &operator-(const Box &obj1, const Box &obj2){
	Box *newObj=new Box;
	newObj->setH(obj1.getH()-obj2.getH());
	newObj->setL(obj1.getL()-obj2.getL());
	newObj->setW(obj1.getW()-obj2.getW());
	return *newObj;
}
Box &operator+(const Box &obj, float num){
	Box *newObj=new Box;
	newObj->setH(obj.getH()+num);
	newObj->setL(obj.getL()+num);
	newObj->setW(obj.getW()+num);
	return *newObj;
}
Box &operator-(const Box &obj, float num){
	Box *newObj=new Box;
	newObj->setH(obj.getH()-num);
	newObj->setL(obj.getL()-num);
	newObj->setW(obj.getW()-num);
	return *newObj;
}
Box &operator*(const Box &obj, float num){
	Box *newObj=new Box;
	newObj->setH(obj.getH()*num);
	newObj->setL(obj.getL()*num);
	newObj->setW(obj.getW()*num);
	return *newObj;
}
Box &operator/(const Box &obj, float num){
	Box *newObj=new Box;
	newObj->setH(obj.getH()/num);
	newObj->setL(obj.getL()/num);
	newObj->setW(obj.getW()/num);
	return *newObj;
}
bool operator==(const Box &obj1, const Box &obj2){
	float accuracy=0.00001;
	if(fabs(obj1.getH()-obj2.getH())>accuracy)
		return false;
	if(fabs(obj1.getW()-obj2.getW())>accuracy)
		return false;
	if(fabs(obj1.getL()-obj2.getL())>accuracy)
		return false;
	return true;
}
bool operator!=(const Box &obj1, const Box &obj2){
	return !(obj1==obj2);
}
ostream &operator<<(ostream &o, const Box &obj){
	o<<"length: "<<obj.getL()<<", width: "<<obj.getW()<<", height: "<<obj.getH();
	return o;
}