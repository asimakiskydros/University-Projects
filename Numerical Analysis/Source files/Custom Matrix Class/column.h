#ifndef EX_3_COLUMN_H
#define EX_3_COLUMN_H

#include "matrix.h"

class column: public matrix{
public:
    explicit column(int length):matrix(length,1){}
    double get(int index_i) const{
        return matrix::get(index_i,0);
    }
    bool set(int index_i, double value){
        return matrix::set(index_i, 0, value);
    }
};

#endif //EX_3_COLUMN_H
