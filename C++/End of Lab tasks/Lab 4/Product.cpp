#include "Product.h"
#include <cstring>

Product::Product(){
    name=nullptr;
    mass=0;
}
Product::Product(char *s,Date expdt,int m){
    name=new char[strlen(s)+1];
    strcpy(name,s);
    mass=m;
    expiry=expdt;
}
Date Product::getExpiry(){return expiry;}
char *Product::Getname(){return name;}