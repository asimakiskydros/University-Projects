#include <iostream>
#include <cmath>
#include <fstream>
#include "square_matrix.h"
#include "column.h"

#define TOLERANCE 0.00005

column* gauss(const square_matrix&, const column&);
square_matrix** LU(const square_matrix&);
square_matrix* cholesky(const square_matrix&);
column* gauss_seidel(const square_matrix&, const column&, const double&);

int main() {
    std::ofstream ofs;
    int N=10;
    ofs.open("Gauss and Cholesky for N=10.txt",std::ios::out);
    if(ofs.is_open()){
        auto *A = new square_matrix(N);
        auto* B = new column(N);
        //initialize A
        for (int i = 0; i < N; i++) {
            A->set(i, i, 5);
            A->set(i, i + 1, -2);
            A->set(i + 1, i, -2);
        }
        //initialize B
        for (int i = 1; i < N - 1; i++)
            B->set(i, 1);
        B->set(0, 3);
        B->set(N - 1, 3);

        //show A, B
        ofs<< "A______" << std::endl;
        A->print(ofs);
        ofs<< std::endl << "B______" << std::endl;
        B->print(ofs);

        //print output of Gauss
        ofs<< std::endl << "X through Gauss:" << std::endl;
        column *x = gauss(*A, *B);
        if(x != nullptr) x->print(ofs);
        delete x;

        //print output of Cholesky
        ofs<< std::endl << "Cholesky L of A:" << std::endl;
        square_matrix *L = cholesky(*A);
        L->print(ofs);
        delete L;

        delete A;
        delete B;

        ofs.close();
    }
    else
        std::cerr<<"Error when opening file"<<std::endl;

    for(int j = 0;j < 2; j++, N*=1000){
        ofs.open(N == 10 ? "Gauss-Seidel for N = 10.txt" : "Gauss-Seidel for N = 10000.txt",std::ios::out);
        if(ofs.is_open()) {
            auto *A = new square_matrix(N);
            auto* B = new column(N);
            //initialize A
            for (int i = 0; i < N; i++) {
                A->set(i, i, 5);
                A->set(i, i + 1, -2);
                A->set(i + 1, i, -2);
            }
            //initialize B
            for (int i = 1; i < N - 1; i++)
                B->set(i, 1);
            B->set(0, 3);
            B->set(N - 1, 3);

            //print output of Gauss-Seidel
            ofs<< std::endl << "X through Gauss-Seidel:" << std::endl;
            column *x = gauss_seidel(*A, *B, TOLERANCE);
            if(x != nullptr) x->print(ofs);
            delete x;
            ofs<< std::endl;

            delete A;
            delete B;

            ofs.close();
        }
        else
            std::cerr<<"Error when opening file"<<std::endl;
    }

    return 0;
}
column* gauss_seidel(const square_matrix &A, const column &B, const double &tolerance){
    int temp_length = A.get_length();

    //make sure A and B have the same length
    if(temp_length != B.get_length())
        return nullptr;

    //make sure A has a dominant diagonal
    for(int i = 0; i< temp_length; i++){
        double sum = 0;
        for(int j = 0; j < temp_length; j++)
            if(i != j) sum += std::abs(A.get(i,j));
        if(std::abs(A.get(i,i)) < sum) {
            std::cout << "Given square matrix A doesn't have a dominant diagonal, process won't converge"<<std::endl;
            return nullptr;
        }
    }

    //initialize new x matrix, all zero's
    auto *x = new column(temp_length);
    column* error = nullptr;
    do{
        delete error;
        error = (column *)x->copy();
        //Since the x matrix can be updated on loop time, there's no need for a second matrix
        //that holds the previous x_i. X_i's get updated from start to finish, therefore
        //we still have that for j<i the algorithm uses (m+1) x's and for j>1 it uses (m) x's
        for(int i = 0;i < temp_length; i++){
            double sum = 0;
            for(int j = 0; j < temp_length; j++)
                if(i != j)
                    sum += A.get(i, j)*x->get(j);

            x->set(i, (B.get(i) - sum)/A.get(i, i));
            //update the error matrix
            //(therefore at the end of the loop, for i=0,....,n-1: error[i] = x[i]^(m+1) - x[i]^(m))
            error->set(i, x->get(i) - error->get(i));
        }
    }while(error->infinity_norm() >= tolerance);

    return x;
}
square_matrix* cholesky(const square_matrix &A){
    //"A" assumed symmetrical and positive-definite
    int temp_length = A.get_length();
    auto* L = new square_matrix(temp_length);

    for(int i = 0; i < temp_length; i++){
        double sum;
        //i>j case
        for(int j = 0; j < i; j++){
            sum = 0;
            for(int k = 0; k < j; k++)
                sum += L->get(i, k)*L->get(j, k);
            L->set(i, j, (A.get(i, j) - sum)/L->get(j, j));
        }
        //i==j case
        sum = 0;
        for(int k=0;k<i;k++)
            sum += L->get(i, k)*L->get(i, k);
        L->set(i, i, sqrt(A.get(i, i) - sum));
    }
    return L;
}
column* gauss(const square_matrix &A, const column &B){
    int temp_length = A.get_length();

    //make sure A and B have the same length
    if(temp_length != B.get_length())
        return nullptr;

    //decompose A (remember that bag[0] = L, bag[1] = U, bag[2] = P)
    square_matrix** bag = LU(A);
    auto* PB = (square_matrix*)multiply(*bag[2],B);
    //P is no longer needed
    delete bag[2];

    //step 1: L * y = PB, solve for y
    //add all previous values up until the corresponding diagonal position with the already found y's
    //then the equation becomes : sum + 1*y[i] = Pb[i] => y[i] = Pb[i] - sum
    auto *y = new column(temp_length);
    for(int i = 0; i < temp_length; i++){
        double sum = 0;
        for(int j = 0; j < i; j++)
            sum += y->get(j)*bag[0]->get(i, j);
        y->set(i, PB->get(i, 0) - sum);
    }
    //PB and L no longer needed
    delete PB;
    delete bag[0];

    //step 2: Now that y is known, solve Ux = y
    auto *x = new column(temp_length);
    //repeat the previous process but from the bottom-up
    for(int i = temp_length - 1; i >= 0; i--){
        double sum = 0;
        for(int j = i + 1; j < temp_length; j++)
            sum += x->get(j)*bag[1]->get(i, j);
        x->set(i, (y->get(i) - sum)/bag[1]->get(i,i));
    }
    //delete the rest
    delete bag[1];
    delete [] bag;
    delete y;

    return x;
}
square_matrix** LU(const square_matrix &A){
    int temp_length = A.get_length();
    //create unitary diagonal P and L
    auto* P = new square_matrix(temp_length);
    auto* L = new square_matrix(temp_length);
    for(int i=0;i<temp_length;i++) {
        P->set(i, i, 1);
        L->set(i, i, 1);
    }
    //create U copy of A
    auto* U = (square_matrix*)A.copy();

    for(int j = 0; j < temp_length; j++){
        //find the row with the absolute max value at the "driver" position
        int row_holds_max = j, row;
        for(row = j + 1; row < temp_length; row++)
            if(std::abs(U->get(row, j)) > std::abs(U->get(j ,j)))
                row_holds_max = row;

        //swap driver row with row_holds_max
        P->swap_rows(j, row_holds_max);
        U->swap_rows(j, row_holds_max);

        //eliminate all values under driver
        for(int i = j + 1; i < temp_length; i++){
            //store coefficient_i (a_ij/a_jj)
            L->set(i, j,  U->get(i, j)/U->get(j, j));
            U->set(i, j, 0);
        }
        //update the lines' other values
        for(int i = j + 1;i < temp_length; i++)
            for(int h = j + 1; h < temp_length; h++)
                // - c_ij*l_j + li
                U->set(i, h, -1*L->get(i,j)*U->get(j,h) + U->get(i,h));
    }
    //return the decomposed matrices
    auto** ret = new square_matrix*[3];
    ret[0] = L;
    ret[1] = U;
    ret[2] = P;

    return ret;
}
