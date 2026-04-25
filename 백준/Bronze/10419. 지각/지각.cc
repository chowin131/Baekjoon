#include<bits/stdc++.h>
using namespace std;
int T,d,t;
main(){
cin>>T;
while(T--){
cin>>d;t=0;
while(t*t+t<=d)t++;
cout<<t-1<<"\n";
}
}