#ifndef Savings_h
#define Savings_h
#include "Account.h"
class Savings:public Account{
    private:
        int withdraw_counter=0;
    public:
        Savings(char*);
        Savings(char*,float);
        bool withdraw(float);
};
#endif