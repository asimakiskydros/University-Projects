#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <ctime>
#include <random>
#include <set>
#include <memory>
#include "square_matrix.h"
#include "column.h"

#ifndef M_PI

#define M_PI 3.14159265

#endif

struct cubic_spline{
    //a + b(x-x_0) + c(x-x_0)^2 + d(x-x_0)^3
    double a,b,c,d,x_0;
};

bool belongs_in(double, double, double); //checks if first value belongs in [second, third]
double sin_lagrange(double);
double sin_splines(double);
double sin_least_squares(double, int);
column* gauss(const square_matrix &, const column &);
square_matrix** LU(const square_matrix &);
std::shared_ptr< std::vector< std::pair< double, double >>> get_points(); //chosen points initializer
std::shared_ptr< std::vector< cubic_spline >> get_splines();
std::shared_ptr< std::vector<double>> get_coefficients(int);

int main() {
    std::ofstream file_output;
    std::ofstream file_lagrange;
    std::ofstream file_splines;
    std::ofstream file_least_squares;
    std::mt19937 engine(time(nullptr) + 1);
    std::uniform_real_distribution<double> urd(-1*M_PI, M_PI);

    //random numbers must be unique
    std::set<double> bag_uniques;
    while(bag_uniques.size() < 200)
        bag_uniques.insert(urd(engine));

    file_output.open("output.txt");
    file_lagrange.open("lagrange.txt");
    file_splines.open("splines.txt");
    file_least_squares.open("least_squares.txt");

    if(!file_output.is_open()) return 1;
    if(!file_lagrange.is_open()) return 2;
    if(!file_splines.is_open()) return 3;
    if(!file_least_squares.is_open()) return 4;

    for(const double &number : bag_uniques) {
        double actual = sin(number);
        double approx_lagrange = sin_lagrange(number);
        double approx_splines = sin_splines(number);
        double approx_least_squares = sin_least_squares(number, 3);
        file_output << "[" << number << "]" <<
                    "\n   actual: " << actual <<
             "\n   through lagrange: " << approx_lagrange <<
                " (error = " << std::abs(actual - approx_lagrange) <<
             ")\n   through splines: " << approx_splines <<
                " (error = " << std::abs(actual - approx_splines) <<
             ")\n   through least squares: " << approx_least_squares <<
                " (error = " << std::abs(actual - approx_least_squares) <<
             ")\n";
        file_lagrange << number << " " << std::abs(actual - approx_lagrange) << "\n";
        file_splines << number << " " << std::abs(actual - approx_splines) << "\n";
        file_least_squares << number << " " << std::abs(actual - approx_least_squares) << "\n";
    }
    file_output.close();
    file_lagrange.close();
    file_splines.close();
    file_least_squares.close();

    return 0;
}

std::shared_ptr<std::vector<std::pair<double, double>>> get_points(){
    std::vector< std::pair<double, double> > list = {
            {-1*M_PI, 0},
            {-0.5*M_PI, -1},
            {-0.25*M_PI, -0.707106},
            {-0.125*M_PI, -0.382683},
            {0, 0},
            {1, 0.841470},
            {0.125*M_PI, 0.382683},
            {0.25*M_PI, 0.707106},
            {0.5*M_PI, 1},
            {M_PI, 0}
    };

    return std::make_shared<std::vector<std::pair<double,double>>>(std::move(list));
}

double sin_lagrange(double number){
    static auto points = get_points();
    double sum = 0;

    for(const auto &point : *points){
        double numerator = 1;
        double denominator = 1;
        for(const auto &other_point : *points) {
            if (&point == &other_point) continue;
            /*
             * numerator : *= (x - x_j) at every cycle
             * denominator: *= (x_i - x_j) at every cycle
             * x_i <> x_j
             */
            numerator *= number - other_point.first;
            denominator *= point.first - other_point.first;
        }
        //         y_i      *          L_i(x)
        sum += point.second * numerator / denominator;
    }
    return sum;
}

double sin_splines(double number){
    static auto splines = get_splines();
    static auto points = get_points();
    int size_points = (int)points->size();

    //number must be in [start, finish]
    if(!belongs_in(number, (*points)[0].first, (*points)[size_points - 1].first))
        throw std::invalid_argument("Parameter out of bounds");

    int i;
    double x;
    for(i = 0; i < size_points - 1; i++)
        if(belongs_in(number, (*points)[i].first, (*points)[i + 1].first)){
            x = (number - (*splines)[i].x_0);
            return (*splines)[i].a + (*splines)[i].b*x + (*splines)[i].c*x*x + (*splines)[i].d*x*x*x;
        }

    //this shouldn't be reachable, so error message
    return -11111111;
}

double sin_least_squares(double number, int power_polynomial){
    //integer parameter determines approx polynomial's max power
    //polynomials of power n hold n+1 coefficients (+ const)
    int num_coefficients = power_polynomial + 1;
    static auto coefficients = get_coefficients(num_coefficients);

    double sum = (*coefficients)[0];
    double powered_x = number;
    for(int i = 1; i < num_coefficients; i++){
        sum += (*coefficients)[i] * powered_x;
        powered_x *= number;
    }

    return sum;
}

std::shared_ptr<std::vector< cubic_spline>> get_splines(){
    /*
     * Algorithm found in wikipedia (in pseudocode)
     * https://en.wikipedia.org/wiki/Spline_(mathematics)
     */

    //array of points, size of n+1
    static auto points = get_points();

    //therefore length == n
    unsigned int length = points->size() - 1;

    //set array "a" of all values
    std::vector<double> a;
    for(const auto &point : *points)
        a.emplace_back(point.second);

    //set array "h" of all differences x[i+1]-x[i], i = 0....n-1
    std::vector<double> h(length);
    for(int i = 0; i < length; i++)
        h[i] = (*points)[i + 1].first - (*points)[i].first;
    //set array "alpha" of 3(a[i+1] - a[i])/h[i] - 3(a[i] - a[i-1])/h[i-1], i = 1....n-1
    std::vector<double> alpha(length);
    for(int i = 1; i < length; i++)
        alpha[i] = 3*((a[i + 1] - a[i])/h[i] - (a[i] - a[i - 1])/h[i - 1]);

    //prepare arrays b, d, c, l, m, z
    std::vector<double> b(length), d(length), c(length + 1), l(length + 1), m(length + 1) ,z(length + 1);
    //input data to arrays according to wikipedia formulas
    l[0] = 1;
    m[0] = z[0] = 0;
    for(int i = 1 ; i < length; i++){
        l[i] = 2*((*points)[i + 1].first - (*points)[i - 1].first) - h[i - 1]*m[i - 1];
        m[i] = h[i]/l[i];
        z[i] = (alpha[i] - h[i - 1]*z[i - 1])/l[i];
    }
    l[length] = 1;
    z[length] = c[length] = 0;
    for(int j = (int)length - 1; j >= 0; j--){
        c[j] = z[j] - m[j]*c[j + 1];
        b[j] = (a[j + 1] - a[j])/h[j] - h[j]*(c[j + 1] + 2*c[j])/3;
        d[j] = (c[j + 1] - c[j])/(3*h[j]);
    }

    //create splines set and inform each of its members with appropriate data
    std::vector<cubic_spline> output_set(length);
    for(int i = 0; i < length; i++){
        output_set[i].a = a[i];
        output_set[i].b = b[i];
        output_set[i].c = c[i];
        output_set[i].d = d[i];
        output_set[i].x_0 = (*points)[i].first;
    }
    return std::make_shared<std::vector<cubic_spline>>(std::move(output_set));
}

bool belongs_in(double number, double start_domain, double finish_domain){
    //true if number in [start, finish]
    return number >= start_domain && number <= finish_domain;
}

std::shared_ptr<std::vector<double>> get_coefficients(int num_coefficients){
    static auto points = get_points();
    //trying to find the line with the smallest possible maximum distance error
    //thus we have the following model: y = a*(1) + b*x
    int length = (int)points->size();

    //matrix A has the first column be completely all 1's and the second all the x[i]'s
    //column B carries all the y[i]'s (all this because of the model)
    matrix A(length, num_coefficients);
    column B(length);
    for(int i = 0; i < length; i++){
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