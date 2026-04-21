#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--){
        int x,y;
        cin>>x>>y;
        int d=y-x;
        int k=sqrt(d);
        if(k*k==d)cout<<2*k-1<<'\n';
        else if(d<=k*k+k)cout<<2*k<<'\n';
        else cout<<2*k+1<<'\n';
    }
}