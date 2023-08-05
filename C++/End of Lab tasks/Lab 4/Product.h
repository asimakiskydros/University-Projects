#ifndef PRODUCT_H
#define PRODUCT_H
#include "Date.h"
class Product{
    protected:
        char *name;
        int mass;
        Date expiry;
    public:
        Product();
        Product(char*,Date,int);
        virtual Date getExpiry();
        char *Getname();
};
#endif //PRODUCT_H