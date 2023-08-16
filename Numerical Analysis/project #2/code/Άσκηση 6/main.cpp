#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <fstream>

double integral_sin_table_method(double, double, int);
double integral_sin_simpson(double, double, int);
std::shared_ptr<std::vector<double>> divide_domain_equal(double, double, int);

int main() {
    double result_tables = integral_sin_table_method(0, M_PI*0.5, 11);
    double result_simpson = integral_sin_simpson(0, M_PI*0.5, 11);
    //max{x in [0,pi/2]}{ |(sin(x))''|} == max{x in [0,pi/2]}{ |(sin(x))^(4)|} = 1
    double expected = 1;
    double range = M_PI*0.5; //(b-a)

    std::ofstream file;
    file.open("output.txt");
    if(!file.is_open()) return 1;

    file << "Integral of sin(x) in [0, pi/2]:"
    << "\n\n   * through the table method: " << result_tables
    << "\n        (numerical error = " << std::abs(expected - result_tables) << ")"
    << "\n        (maximum theoretical error = " << std::fixed << range * range * range / (12 * 11 * 11) << ")"
    << "\n\n   * through Simpson's method: " << result_simpson
    << "\n        (numerical error = " << std::abs(expected - result_simpson) << ")"
    << "\n        (maximum theoretical error = " << std::fixed
    <<                   range * range * range * range * range / (180 * 11 * 11 * 11 * 11) << ")";
    file.close();

    return 0;
}

double integral_sin_table_method(double start, double finish, int num_points){
    int N = num_points - 1;
    auto points = divide_domain_equal(start, finish, N);
    //E = (b-a)/2N [f(x_0) + f(x_N) + 2sum{i,1,n-1}(f(x_i))] =>
    //E = (b-a)/N [f(x_0)/2 + f(x_N)/2 + sum{i,1,n-1}(f(x_i))]
    double factor = (finish - start) / N;
    double sum = 0.5*(sin(start) + sin(finish));

    for(int i = 1; i < N; i++)
        sum += sin((*points)[i]);

    return factor * sum;
}

double integral_sin_simpson(double start, double finish, int num_points){
    int N = num_points - 1;
    auto points = divide_domain_equal(start, finish, N);
    //E = (b-a)/3N [f(x_0) + f(x_N) + 4sum{i,1,n/2}(f(x_{2i-1})) + 2sum{i,1,n/2 - 1}(f(x_{2i}))]
    double factor = (finish - start) / (3 * N);
    double sum_even_points = 0;
    double sum_odd_points = 0;

    for(int i = 1; i <= N * 0.5; i++)
        sum_odd_points += sin((*points)[2*i - 1]);
    for(int i = 1; i < N * 0.5; i++)
        sum_even_points += sin((*points)[2*i]);

    return factor * (sin(start) + sin(finish) + 4 * sum_odd_points + 2 * sum_even_points);
}

std::shared_ptr<std::vector<double>> divide_domain_equal(double start, double finish, int parts){
    //divide domain [start, finish] in (parts) equal parts;
    std::vector<double> points;
    double length = (finish - start) / parts;

    for(double place = start; place <= finish;) {
        points.emplace_back(place);
        place += length;
    }

    return std::make_shared<std::vector<double>>(std::move(points));
}