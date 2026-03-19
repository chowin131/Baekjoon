#include <bits/stdc++.h>
using namespace std;
void func(int n,int s,int e,int m){
    if(n==1) cout<<s<<" "<<e<<"\n";
    else{
        func(n-1,s,m,e);
        cout<<s<<" "<<e<<"\n";
        func(n-1,m,e,s);
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    cout<<(1<<n)-1<<"\n";
    func(n,1,3,2);
}