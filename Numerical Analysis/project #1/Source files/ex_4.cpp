#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include "square_matrix.h"
#include "column.h"

#define TOLERANCE 0.00000005 // 1/2 * 10^-7

bool is_stochastic(const square_matrix&);
column* power_method(const square_matrix&, const double&, double&);
square_matrix* get_google_matrix(const square_matrix&,const double&);

int main() {
    std::ofstream ofs;
    ofs.open("output.txt",std::ios::out);
    if(ofs.is_open()) {
        auto *A = new square_matrix(15);
        //initialize A matrix
        int i_index[] = {0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8,
                         8, 8, 9, 10, 11, 11, 11, 12, 12, 13, 13, 13, 13, 14, 14};
        int j_index[] = {1, 8, 2, 4, 6, 1, 5, 7, 2, 11, 0, 9, 9, 10, 9, 10, 3, 10,
                         4, 5, 9, 12, 14, 6, 7, 10, 8, 13, 9, 10, 12, 14, 11, 13};
        for (int i = 0; i < 34; i++)
            A->set(i_index[i], j_index[i], 1);
        ofs << "A_____" << std::endl;
        A->print(ofs);
        ofs << std::endl;

        //Initialize Google Matrix (q = 0.15)
        square_matrix* Google = get_google_matrix(*A,0.15);

        ofs << "Google (q = 0.15)_____" << std::endl;
        Google->print(ofs);
        ofs << std::endl;

        //a)
        ofs << "a)__________________________________________________________" << std::endl;
        if (is_stochastic(*Google))
            ofs << "Google matrix is stochastic, as all its columns sum to 1" << std::endl << std::endl;
        else
            ofs << "Found at least one column where sum is not 1, thus Google matrix is not stochastic"<< std::endl
            << std::endl;

        //b)
        ofs << "b)__________________________________________________________" << std::endl;
        double maximum_eigenvalue;
        column *p = power_method(*Google, TOLERANCE, maximum_eigenvalue);
        ofs << std::endl << "p______" << std::endl;
        p->print(ofs);
        ofs << std::endl << "lamda = " << maximum_eigenvalue << std::endl << std::endl;
        //this will be useful at following steps
        auto* temp = (column*)p->copy();

        delete Google;
        delete p;

        //c)
        ofs << "c)__________________________________________________________" << std::endl;
        ofs<< "Increasing rank of node 14:"<<std::endl;
        A->set(13, 9, 0);
        A->set(8, 13, 1);
        A->set(9, 13, 1);
        A->set(10, 13, 1);
        A->set(11, 13, 1);

        Google = get_google_matrix(*A,0.15);
        p = power_method(*Google, TOLERANCE, maximum_eigenvalue);

        ofs << "Probability of site[13] (14) before alteration: "<<temp->get(13)<<std::endl;
        ofs << "Probability of site[13] (14) after alteration: "<<p->get(13)<<std::endl<<std::endl;


        ofs << "Google (q = 0.15)_____" << std::endl;
        Google->print(ofs);
        ofs << std::endl;

        ofs << std::endl << "p______" << std::endl;
        p->print(ofs);
        ofs << std::endl << "lamda = " << maximum_eigenvalue << std::endl << std::endl;

        delete Google;
        delete p;

        //d)
        ofs << "d)__________________________________________________________" << std::endl;
        Google = get_google_matrix(*A,0.02);
        ofs << "Google (q = 0.02)_____" << std::endl;
        Google->print(ofs);
        ofs << std::endl;

        p = power_method(*Google, TOLERANCE, maximum_eigenvalue);
        ofs << std::endl << "p______" << std::endl;
        p->print(ofs);
        ofs << std::endl << "lamda = " << maximum_eigenvalue << std::endl << std::endl;

        delete Google;
        delete p;

        Google = get_google_matrix(*A,0.6);
        ofs << "Google (q = 0.6)_____" << std::endl;
        Google->print(ofs);
        ofs << std::endl;

        p = power_method(*Google, TOLERANCE, maximum_eigenvalue);
        ofs << std::endl << "p______" << std::endl;
        p->print(ofs);
        ofs << std::endl << "lamda = " << maximum_eigenvalue << std::endl << std::endl;

        delete Google;
        delete p;

        //e)
        ofs << "e)__________________________________________________________" << std::endl;
        //revert changes to go back to original graph
        A->set(13, 9, 0);
        A->set(8, 13, 1);
        A->set(9, 13, 1);
        A->set(10, 13, 1);
        A->set(11, 13, 1);

        ofs << "Attempting to increase rank of site[10] (11) by setting A(8,11),A(12,11) to 3" << std::endl;
        //set A(8,11),A(12,11) to 3
        A->set(7, 10, 3);
        A->set(11, 10, 3);

        Google = get_google_matrix(*A, 0.15);
        p = power_method(*Google,TOLERANCE,maximum_eigenvalue);
        ofs << "Probability of site[10] (11) before alteration: "<<temp->get(10)<<std::endl;
        ofs << "Probability of site[10] (11) after alteration: "<<p->get(10)<<std::endl<<std::endl;
        delete Google;
        delete p;

        //f)
        ofs << "f)__________________________________________________________" << std::endl;
        ofs << "Cutting off node[9] (10):"<<std::endl<<std::endl;
        auto* A_new = new square_matrix(14);
        //copy A, but with row and column 9 cut off
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 15; j++)
                if(j < 9)
                    A_new->set(i, j, A->get(i, j));
                else if(j > 9)
                    A_new->set(i, j - 1, A->get(i, j));
        for(int i = 10; i < 15; i++)
            for(int j = 0; j < 15; j++)
                if(j < 9)
                    A_new->set(i - 1, j, A->get(i, j));
                else if(j > 9)
                    A_new->set(i - 1, j - 1, A->get(i, j));

        delete A;
        ofs << "A_____" << std::endl;
        A_new->print(ofs);
        ofs << std::endl;

        Google = get_google_matrix(*A_new,0.15);
        p = power_method(*Google, TOLERANCE, maximum_eigenvalue);

        ofs << std::endl << "P:          Before                  After" << std::endl;
        for(int i = 0; i < 15 ; i++){
            ofs <<"site ["<<i<<"]:   "<< temp->get(i)<<"               ";
            if(i < 9)
                ofs << p->get(i);
            else if(i == 9)
                ofs << "      N/A";
            else
                ofs << p->get(i - 1);
            ofs << std::endl;
        }

        delete Google;
        delete p;
        delete A_new;
        ofs.close();
    }else
        std::cerr<<"Error when opening file"<<std::endl;

    return 0;
}
square_matrix* get_google_matrix(const square_matrix &A, const double &jump_probability){
    int N = A.get_length();
    auto *Google = new square_matrix(N);

    //initialize Google matrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double sum = 0;
            //n_j
            for (int k = 0; k < N; k++)
                sum += A.get(j, k);

            //q/n + a(j,i)(1 - q)/n_j
            //for q = 0.15, n = 15, n_j = sum this becomes:
            Google->set(i, j, jump_probability/N + (1 - jump_probability)* A.get(j, i) / sum);
        }

    return Google;
}
bool is_stochastic(const square_matrix &A){
    int temp_length = A.get_length();
    //assume true, sum all columns and check if they return 1
    for(int i = 0; i < temp_length; i++){
        double sum = 0;
        for(int j = 0; j < temp_length; j++)
            sum += A.get(j, i);
        if(sum != 1)
            //at least one column has sum <> 1, matrix is not stochastic
            return false;
    }
    return true;
}
column *power_method(const square_matrix &A, const double &tolerance, double &lamda){
    int temp_length = A.get_length();

    //initialize a random vector
    //to minimize the chance that it is vertical to the eigenvector
    auto *dominant_eigenvector = new column(temp_length);
    std::mt19937 engine(time(nullptr) + 0);
    std::uniform_real_distribution<double> urd(0,1);
    for(int i = 0; i < temp_length; i++)
        dominant_eigenvector->set(i, urd(engine));

    lamda = 0;
    double lamda_prev;
    do{
        lamda_prev = lamda;
        column *temp = dominant_eigenvector;
        //b = Ab
        dominant_eigenvector = (column*)multiply(A,*dominant_eigenvector);
        delete temp;

       //find eigenvalue - first nonzero value
        for(int i = 0; i < temp_length; i++)
            if((lamda = dominant_eigenvector->get(i)) != 0)
                break;

        //normalize matrix
        for(int i = 0; i < temp_length; i++)
            dominant_eigenvector->set(i, dominant_eigenvector->get(i)/lamda);

        //terminate when  | l_current - l_prev | < e
    }while(std::abs(lamda - lamda_prev) >= tolerance);

    //final normalization to a probability vector
    double sum = 0;
    for(int i = 0; i <temp_length; i++)
        sum += dominant_eigenvector->get(i);
    for(int i = 0; i <temp_length; i++)
        dominant_eigenvector->set(i, dominant_eigenvector->get(i)/sum);

    return dominant_eigenvector;
}
