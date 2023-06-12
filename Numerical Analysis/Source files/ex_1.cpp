#include <iostream>
#include <iomanip>
#include <cmath>

#define TOLERANCE 0.000005 // 1/2 * 10^-5

using namespace std;

double f(double x){
    // f(x) = 14xe^(x−2) − 12e^(x-2) - 7x^3 + 20x^2 - 26x + 12
    return 14*x*exp(x-2) - 12*exp(x-2) - 7*x*x*x + 20*x*x - 26*x + 12;
}
double f_der1(double x){
    // f'(x) = 14xe^(x-2) + 2e^(x-2) - 21x^2 + 40x - 26
    return 14*x*exp(x-2) + 2*exp(x-2) - 21*x*x + 40*x - 26;
}
double f_der2(double x){
    // f''(x) = 14xe^(x-2) + 16e^(x-2) - 42x + 40
    return 14*x*exp(x-2) + 16*exp(x-2) -42*x + 40;
}
bool check_bolzano(double start, double finish, int cycles){
    //make sure Bolzano's prerequisites are met
    double f_start = f(start);
    double f_finish = f(finish);
    if(f_start*f_finish > 0){
        cout<<"Bolzano's prerequisites aren't met, process can't continue"<<endl;
        return false;
    }
    //eliminate case where parameter is root
    if(f_start == 0)
        cout << " ->x ~= " << fixed << setprecision(5) << start << " (took "<<cycles<<" cycle)" << endl;
    if(f_finish == 0)
        cout << " ->x ~= " << fixed << setprecision(5) << finish << " (took "<<cycles<<" cycle)" << endl;
    if(f_start == 0 || f_finish == 0)
        return false;

    return true;
}

void bisection_method(double start,double finish,const double &tolerance){
    //N > [ln(b -a ) - ln(e) / ln(2)] therefore N is that, ceiling-ed----------V
    int cycles = (int)((log(finish - start) - log(tolerance)) / log(2) + 1);
    double midpoint;

    for(int i=0;i<cycles;i++){
        if(!check_bolzano(start,finish,i+1))
            return;

        midpoint = (start + finish) / 2;
        //start, midpoint same sign case
        if(f(midpoint)*f(start) < 0)
            finish = midpoint;
        //midpoint, finish same sign case
        else
            start = midpoint;
    }
    //exiting the loop, [start,finish] is now the final subset, therefore its midpoint is the sufficient approx.
    cout<<" ->x ~= "<<fixed<<setprecision(5)<<(finish + start)/2<<" (took "<<++cycles<<" cycles)"<<endl;
}

void newton_raphson_method(double start, double finish,const double &tolerance){
    if(!check_bolzano(start, finish,1))
        return;

    double error;
    int cycles = 0;
    double x_now,x_prev = start;
    //Pick x_0 so that f(x_0)f''(x_0) > 0
    if(f(start)* f_der2(start) <= 0 && f(finish)* f_der2(finish) > 0)
        x_prev = finish;

    do{
        cycles++;

        // x_n = x_n-1 - f(x_n-1)/f'(x_n-1)
        x_now = x_prev - (f(x_prev)/ f_der1(x_prev));
        error = abs(x_now - x_prev);
        x_prev = x_now;

        //end when final error < tolerance
    }while(error >= tolerance);

    cout<<" ->x ~= "<<fixed<<setprecision(5)<<x_now<<" (took "<<cycles<<" cycles)"<<endl;
}
void secant_method(double start, double finish, const double &tolerance){
    if(!check_bolzano(start,finish,1))
        return;

    double error;
    int cycles = 0;
    double x;
    do{
        cycles++;

        //x_n+1 = x_n - (f(x_n)(x_n - x_n-1))/(f(x_n) - f(x_n-1))
        x = finish - (f(finish)*(finish - start)/(f(finish) - f(start)));

        error = abs(x - finish);
        start = finish;
        finish = x;
        //end when final error < tolerance
    }while(error >= tolerance);

    cout<<" ->x ~= "<<fixed<<setprecision(5)<<x<<" (took "<<cycles<<" cycles)"<<endl;
}

int main() {
    cout<<"---------------------------------------------------------------------------------------"<<endl;
    cout<<"The search for the solutions of f(x) = 14xe^(x-2) - 12e^(x-2) - 7x^3 + 20x^2 - 26x + 12"<<endl;
    cout<<"* Through the bisection method:"<<endl;
    bisection_method(0,1,TOLERANCE);
    bisection_method(1.5,3,TOLERANCE);
    cout<<"* Through the Newton-Raphson method:"<<endl;
    newton_raphson_method(0,1,TOLERANCE);
    newton_raphson_method(1.5,3,TOLERANCE);
    cout<<"* Through the secant method:"<<endl;
    secant_method(0,1,TOLERANCE);
    secant_method(1.5,3,TOLERANCE);
    cout<<"---------------------------------------------------------------------------------------"<<endl;
    return 0;
}
