#include "PackedProduct.h"

PackedProduct::PackedProduct():Product(){isOpen=lifetime=0;}
PackedProduct::PackedProduct(char *s,Date expdt,int m,bool opn,int lt, Date dt_opn):Product(s,expdt,m){
    isOpen=opn;
    lifetime=lt;
    date_opened=dt_opn;
}
Date PackedProduct::getExpiry(){
    if(!isOpen)
        return expiry;
    Date temp=date_opened;
    temp.add(lifetime);
    return temp;
}