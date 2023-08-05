#ifndef ACCOUNT_H
#define ACCOUNT_H
class Account{
    protected:
        float balance;
        char *description;
    public:
        Account(char *);
        Account (char *,float);
        virtual bool withdraw(float);
        bool deposit(float);
        float getBalance();
        char *getDescription();
};
#endif // ACCOUNT_H