#include <iostream>
#include "storage.h"
#include <string>
using namespace std;
int main()
{
 int *A,n,count;
 string *St;
 cin>>count;
 for (int i=0;i<count;i++)
 {
 cin>>n;
 A = new int[n];
 St = new string[n];
 for (int i=0;i<n;i++)
 cin>>A[i]>>St[i];
 storage<int> I(A,n);
 storage<string> S(St,n);
 A[0] =A[n-1]=0;
 St[0] = St[n-1] = "_";
 I[0] = I[n-1] = 100;
 S[0] = S[n-1] = "*";
 for (int i=0;i<n;i++)
 cout<<I[i] << " " << S[i] << endl;
 }
}