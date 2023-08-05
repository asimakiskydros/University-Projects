#include <iostream>
#include <string>
using namespace std;
#include "foo.h"
int main()
{

 string s1,s2;
 int d1,d2,n;
 cin>>n;
 for (int i=0;i<n;i++)
 {
 cin>>s1>>d1>>s2>>d2;
 foo a(s1,d1);
 a+=2;
 foo b = a + foo(s2,d2);
 cout<<a<<endl<<b<<endl;
 }
}