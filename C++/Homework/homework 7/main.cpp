#include <iostream>
#include <string>
#include "myFunctions.h"
using namespace std;


template <typename T>
void process (T &m, int n)
{
    T *A = read(n,m);
    if (median(A,n,m))
    {
        cout<<"Median is "<<m<<endl;
        mySort(A,n);
        for (int i=0;i<n;i++)
        {
            cout<<"["<<i<<"] "<<A[i]<<compare(A[i],m," is bigger than "," is smaller than "," is equal to ")<<m;
            cout<<" ("<<A[i]<<compare(A[i],m,'>','<', '=')<<m<<')'<<endl;
        }
    }

}


int main()
{
    int type;
    int n;

    cin>>type>>n;

    if (type<0 || type>2 || !(n%2))
    {
        cerr<<"Wrong Input"<<endl;
        return 1;
    }
    switch (type)  // 0 for int, 1 for double, 2 for std::string
    {
        case 0:{
                    int m;
                    process(m,n);
                    break;
               }
        case 1:{
                    double m;
                    process(m,n);
                    break;
               }
        case 2:{
                    string m;
                    process(m,n);
                    break;
               }
    }
    return 0;
}