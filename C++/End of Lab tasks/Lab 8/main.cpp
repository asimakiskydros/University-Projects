#include <iostream>
#include "complex_number.h"

using namespace std;

int main()
{
    double x1,y1,x2,y2;
    complex_number a,b,c;

    cin>>x1>>y1>>x2>>y2;
    cout<<"before: "<<a[0]<<" "<<a[1]<<","<<b[0]<<" "<<b[1]<<endl;
    a[0]=x1;
    a[1]=y1;
    b[0]=x2;
    b[1]=y2;
    c = a/b;
    cout<<"after: "<<a[0]<<" "<<a[1]<<","<<b[0]<<" "<<b[1]<<endl;
    cout<<"Division: "<<c<<endl;
    return 0;
}