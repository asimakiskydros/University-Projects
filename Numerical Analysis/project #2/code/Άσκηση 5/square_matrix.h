#ifndef EX_3_SQUARE_MATRIX_H
#define EX_3_SQUARE_MATRIX_H

#include "matrix.h"

class square_matrix: public matrix{
public:
    explicit square_matrix(int length):matrix(length,length){}
};

#endif //EX_3_SQUARE_MATRIX_H
