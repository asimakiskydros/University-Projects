#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <fstream>
#include "square_matrix.h"
#include "column.h"

double least_squares(double, int, const std::string&);
column* gauss(const square_matrix &, const column &);
square_matrix** LU(const square_matrix &);
std::shared_ptr< std::vector<double>> get_coefficients(int, const std::string&);
std::shared_ptr< std::vector< std::pair< double, double >>> get_points(const std::string&); //chosen points initializer
void print_prediction(std::ofstream&, int, double, const std::string&);


int main() {
    /*
     * Data in files are in the following format:
     * (YY*10000+MM*100+DD) (SHARE)
     * (for year, "20" prefix is neglected, assumed 20YY)
     *
     *
     * Birthday: 15/01/21 (conference happened that day)
     */
    double date_guess1 = 210118, actual_shares_CENER1 = 1.7140, actual_shares_CNLCAP1 = 8.7500;
    double date_guess2 = 210119, actual_shares_CENER2 = 1.7140, actual_shares_CNLCAP2 = 8.7500;
    double date_guess3 = 210120, actual_shares_CENER3 = 1.7260, actual_shares_CNLCAP3 = 8.7500;
    double date_guess4 = 210121, actual_shares_CENER4 = 1.7000, actual_shares_CNLCAP4 = 8.7500;
    double date_guess5 = 210122, actual_shares_CENER5 = 1.6900, actual_shares_CNLCAP5 = 8.7500;
    double date_guess6 = 210125, actual_shares_CENER6 = 1.6500, actual_shares_CNLCAP6 = 8.7500;

    auto points1 = get_points("data_CENER.txt");
    auto points2 = get_points("data_CNLCAP.txt");
    std::ofstream file;
    file.open("output.txt");
    if(!file.is_open()) return 1;

    file << "Predictions for CENER:" << std::fixed;
    print_prediction(file, (int)date_guess1, actual_shares_CENER1, "data_CENER.txt");
    print_prediction(file, (int)date_guess2, actual_shares_CENER2, "data_CENER.txt");
    print_prediction(file, (int)date_guess3, actual_shares_CENER3, "data_CENER.txt");
    print_prediction(file, (int)date_guess4, actual_shares_CENER4, "data_CENER.txt");
    print_prediction(file, (int)date_guess5, actual_shares_CENER5, "data_CENER.txt");
    print_prediction(file, (int)date_guess6, actual_shares_CENER6, "data_CENER.txt");
    file << "\nPredictions of conferences used to build the polynomial (CENER):";
    for(const auto &point : *points1)
        print_prediction(file, (int)point.first, point.second, "data_CENER.txt");

    file << "\nPredictions for CNLCAP:" << std::fixed;
    print_prediction(file, (int)date_guess1, actual_shares_CNLCAP1, "data_CNLCAP.txt");
    print_prediction(file, (int)date_guess2, actual_shares_CNLCAP2, "data_CNLCAP.txt");
    print_prediction(file, (int)date_guess3, actual_shares_CNLCAP3, "data_CNLCAP.txt");
    print_prediction(file, (int)date_guess4, actual_shares_CNLCAP4, "data_CNLCAP.txt");
    print_prediction(file, (int)date_guess5, actual_shares_CNLCAP5, "data_CNLCAP.txt");
    print_prediction(file, (int)date_guess6, actual_shares_CNLCAP6, "data_CNLCAP.txt");
    file << "\nPredictions of conferences used to build the polynomial (CNLCAP):";
    for(const auto &point : *points2)
        print_prediction(file, (int)point.first, point.second, "data_CNLCAP.txt");

    file.close();

    return 0;
}

void print_prediction(std::ofstream &o, int x, double actual, const std::string &filename){
    std::string date_string_format;
    int date_int_format = x;
    //turn int to string format
    while(date_int_format > 0) {
        date_string_format += std::to_string(date_int_format % 100);
        date_int_format /= 100;
        if(date_int_format > 0) date_string_format += "/";
    }
    //print data
    o << "\n    ->at " << date_string_format << ":"
      << "\n        actual: " << actual
      << "\n        power-2 polynomial: " << least_squares(x, 2, filename)
      << "\n        power-3 polynomial: " << least_squares(x, 3, filename)
      << "\n        power-4 polynomial: " << least_squares(x, 4, filename)
      << "\n";
}

double least_squares(double number, int power_polynomial, const std::string &filename){
    //integer parameter determines approx polynomial's max power
    //polynomials of power n hold n+1 coefficients (+ const)
    int num_coefficients = power_polynomial + 1;
    auto coefficients = get_coefficients(num_coefficients, filename);

    double sum = (*coefficients)[0];
    double powered_x = number;
    for(int i = 1; i < num_coefficients; i++){
        sum += (*coefficients)[i] * powered_x;
        powered_x *= number;
    }

    return sum;
}

std::shared_ptr<std::vector<std::pair<double, double>>> get_points(const std::string &filename){
    //data read through file
    std::ifstream file;
    file.open(filename);
    if(!file.is_open()) return nullptr;

    std::vector<std::pair<double, double>> list;
    double date, shares;
    while(file >> date >> shares){
        std::pair<double, double> snapshot(date, shares);
        list.emplace_back(snapshot);
    }

    return std::make_shared<std::vector<std::pair<double,double>>>(std::move(list));
}

std::shared_ptr<std::vector<double>> get_coefficients(int num_coefficients, const std::string &filename){
    auto points = get_points(filename);
    //trying to find the line with the smallest possible maximum distance error
    //thus we have the following model: y = a*(1) + b*x
    int length = (int)points->size();

    //matrix A has the first column be completely all 1's and the second all the x[i]'s
    //column B carries all the y[i]'s (all this because of the model)
    matrix A(length, num_coefficients);
    column B(length);
    for(int i = 0; i <length; i++){
        for(int j = 0; j < num_coefficients; j++)
            A.set(i, j, pow((*points)[i].first, j));
        B.set(i, (*points)[i].second);
    }

    matrix* transpose = A.get_transpose();
    //A*x = b => A^T*A*x = A^T*b
    auto* ATA = (square_matrix*)multiply(*transpose, A);
    auto* ATB = (column*) multiply(*transpose, B);
    delete transpose;

    //solve the system to get the coefficients
    auto* C = gauss(*ATA, *ATB);
    delete ATA;
    delete ATB;

    //return shared ptr of vector of coefficients
    std::vector<double> coefficients;
    if(C != nullptr)
        for(int i = 0; i < num_coefficients; i++)
            coefficients.emplace_back(C->get(i));
    delete C;

    return std::make_shared<std::vector<double>>(std::move(coefficients));
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