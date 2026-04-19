#include<iostream>
using namespace std;
#define int long long
main(){
int a,b,c,d;cin>>a>>b>>c>>d;
if(a+c<b+d)cout<<"Hanyang Univ.";
else if(a+c>b+d)cout<<"Yongdap";
else cout<<"Either";
}