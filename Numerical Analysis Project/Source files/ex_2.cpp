#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <cmath>

#define TOLERANCE 0.000005

using namespace std;

double f(double x){
    //f(x) = 54x^6 + 45x^5 - 102x^4 - 69x^3 + 35x^2 + 16x - 4 xe[-2,2]
    return 54*x*x*x*x*x*x + 45*x*x*x*x*x - 102*x*x*x*x - 69*x*x*x + 35*x*x + 16*x - 4;
}
double f_der1(double x){
    //f'(x) = 324x^5 + 225x^4 - 408x^3 - 207x^2 + 70x + 16
    return 324*x*x*x*x*x + 225*x*x*x*x - 408*x*x*x - 207*x*x + 70*x + 16;
}
double f_der2(double x){
    //f''(x) = 1620x^4 + 900x^3 - 1224x^2 - 414x + 70
    return 1620*x*x*x*x + 900*x*x*x - 1224*x*x - 414*x + 70;
}
bool check_bolzano(double start, double finish,int cycles){
    //make sure Bolzano's prerequisites are met
    double f_start = f(start);
    double f_finish = f(finish);
    if(f_start*f_finish > 0){
        cout<<"Bolzano's prerequisites aren't met, process can't continue"<<endl;
        return false;
    }
    //eliminate case where parameter is root
    if(f_start == 0)
        cout << " ->x ~= " << fixed << setprecision(5) << start << " (took "<<cycles<<" cycles)" << endl;
    if(f_finish == 0)
        cout << " ->x ~= " << fixed << setprecision(5) << finish << " (took "<<cycles<<" cycles)" << endl;
    if(f_start == 0 || f_finish == 0)
        return false;

    return true;
}

void bisection_rand(double start,double finish, const double &tolerance, int factor){
    double guess;
    int cycles = 0;
    double error;

    std::mt19937 engine(time(nullptr) + factor);
    std::uniform_real_distribution<double> urd(start,finish);
    do{
        cycles++;
        if(!check_bolzano(start,finish,cycles))
            return;

        //get random point between start and finish
        guess = urd(engine);

        //b-a/2^N makes no sense here since the algorithm doesn't divide the set at every step
        //assume that the root is still on the midpoint and judge success
        //based on distance of guess from it
        error = abs(guess - (finish + start)/2);

        if(f(guess)*f(start) < 0)
            finish = guess;
        else if(f(finish)*f(guess) < 0)
            start = guess;

        //re-align the distribution
        urd.param(decltype(urd)::param_type(start, finish));

    }while(error >= tolerance);

    cout<<" ->x ~= "<<fixed<<setprecision(5)<<guess<<" (took "<<cycles<<" cycles)"<<endl;
}

void newton_raphson_mod(double start, double finish,const double &tolerance){
    if(!check_bolzano(start,finish,1))
        return;

    //pick starting x_0 so that f(x_0)f''(x_0) > 0
    double x_now,x_prev = start;
    if(f(start)*f_der2(start) <= 0 && f(finish)*f_der2(finish) > 0)
        x_prev = finish;

    int cycles = 0;
    double error;
    do{
        cycles++;

        x_now = x_prev - 1/( (f_der1(x_prev)/f(x_prev)) - 0.5*(f_der2(x_prev)/f_der1(x_prev)) );

        error = abs(x_now - x_prev);
        x_prev = x_now;

    }while(error >= tolerance);

    cout<<" ->x ~= "<<fixed<<setprecision(5)<<x_now<<" (took "<<cycles<<" cycles)"<<endl;
}

void secant_mod(double start, double finish, const double &tolerance){
    if(!check_bolzano(start,finish,1))
        return;

    //let the three starting points be start, finish and midpoint
    double x_res,x_2 = finish, x_1 = (finish + start)/2, x_0 = start;

    double error;
    int cycles = 0;
    double q,r,s;
    do{
        cycles++;
        q = f(x_0)/f(x_1);
        r = f(x_2)/f(x_1);
        s = f(x_2)/f(x_0);
        x_res = x_2 - (r*(r - q)*(x_2 - x_1) + (1 - r)*s*(x_2 - x_0))/((q - 1)*(r - 1)*(s - 1));

        error = abs(x_res - x_2);
        //prepare next cycle
        x_0 = x_1;
        x_1 = x_2;
        x_2 = x_res;

    }while(error >= tolerance);

    cout<<" ->x ~= "<<fixed<<setprecision(5)<<x_res<<" (took "<<cycles<<" cycles)"<<endl;
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
    if(!check_bolzano(start,finish,1))
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
    //->starting domains chosen guarantee that f(a)f(b) < 0 && f'(x),f''(x) <> 0
    //->root in domain [-0.8,-0.6] as shown by the graph is unapproachable because there exists no set where
    //Bolzano's theorem can be used
    cout<<"---------------------------------------------------------------------------------------------------"<<endl;
    cout<<"a) The search for the solutions of f(x) = 54x^6 + 45x^5 - 102x^4 - 69x^3 + 35x^2 + 16x - 4 xe[-2,2]"<<endl;
    cout<<"* Through the modified Newton-Raphson method:"<<endl;
    newton_raphson_mod(-2,-1.3,TOLERANCE);
    newton_raphson_mod(0.15,0.3,TOLERANCE);
    newton_raphson_mod(0.4,0.7,TOLERANCE);
    newton_raphson_mod(1,1.5,TOLERANCE);
    cout<<"* Through the randomized bisection method:"<<endl;
    //"factor" input stirs up the engine, making the guesses even more random
    //its value serves no real purpose, apart from differentiating the initializations of the engines
    //among the different calls of the method
    bisection_rand(-2,-1.3,TOLERANCE,1);
    bisection_rand(0.15,0.3,TOLERANCE,2);
    bisection_rand(0.4,0.7,TOLERANCE,3);
    bisection_rand(1,1.5,TOLERANCE,4);
    cout<<"* Through the modified secant method:"<<endl;
    secant_mod(-2,-1.3,TOLERANCE);
    secant_mod(0.15,0.3,TOLERANCE);
    secant_mod(0.4,0.7,TOLERANCE);
    secant_mod(1,1.5,TOLERANCE);

    cout<<endl;
    cout<<"b) Using randomized bisection for the same root 10 times:"<<endl;
    for(int i=0;i<10;i++)
        bisection_rand(0.15,0.3,TOLERANCE,i + 1);

    cout<<endl;
    cout<<"c) Using the default methods to find the same roots:"<<endl;
    cout<<"* Through the Newton-Raphson method:"<<endl;
    newton_raphson_method(-2,-1.3,TOLERANCE);
    newton_raphson_method(0.15,0.3,TOLERANCE);
    newton_raphson_method(0.4,0.7,TOLERANCE);
    newton_raphson_method(1,1.5,TOLERANCE);
    cout<<"* Through the bisection method:"<<endl;
    bisection_method(-2,-1.3,TOLERANCE);
    bisection_method(0.15,0.3,TOLERANCE);
    bisection_method(0.4,0.7,TOLERANCE);
    bisection_method(1,1.5,TOLERANCE);
    cout<<"* Through the secant method:"<<endl;
    secant_method(-2,-1.3,TOLERANCE);
    secant_method(0.15,0.3,TOLERANCE);
    secant_method(0.4,0.7,TOLERANCE);
    secant_method(1,1.5,TOLERANCE);
    cout<<"---------------------------------------------------------------------------------------------------"<<endl;

    return 0;
}
