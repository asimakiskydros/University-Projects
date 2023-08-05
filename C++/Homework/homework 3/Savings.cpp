#include "Savings.h"

Savings::Savings(char* s):Account(s){}
Savings::Savings(char* s,float bal):Account(s,bal){}
bool Savings::withdraw(float amount){
    if(withdraw_counter>2)
        return false;
    if(amount>balance)
        return false;
    balance-=amount;
    withdraw_counter++;
    return true;
}