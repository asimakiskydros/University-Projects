#include "CreditCard.h"

CreditCard::CreditCard(char* s):Account(s){LIMIT=0;}
CreditCard::CreditCard(char* s,float bal, float lim):Account(s,bal){LIMIT=lim;}
bool CreditCard::withdraw(float amount){
    if(amount<=0)
        return false;
    if(balance+LIMIT>=amount){
        balance-=amount;
        return true;
    }
    return false;
}