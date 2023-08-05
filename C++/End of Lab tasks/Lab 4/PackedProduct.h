#ifndef PACKEDPRODUCT_H
#define PACKEDPRODUCT_H
#include "Product.h"
class PackedProduct:public Product{
    private:
        bool isOpen;
        int lifetime;
        Date date_opened;
    public:
        PackedProduct();
        PackedProduct(char*,Date,int,bool,int,Date);
        Date getExpiry();
};
#endif //PACKEDPRODUCT_H