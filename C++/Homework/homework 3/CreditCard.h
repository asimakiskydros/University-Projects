#ifndef CreditCard_h
#define CreditCard_h
#include "Account.h"
class CreditCard:public Account{
    private:
        float LIMIT;
    public:
        CreditCard(char*);
        CreditCard(char*,float,float);
        bool withdraw(float);
};
#endif