#include<iostream>
#include<cmath>
//#include<bits/stdc++.h>
using namespace std;
void solve()
{
    int n;
    cin>>n;
    int p=sqrt(n);
    cout<<(p*p==n ? true : false)<<endl;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}