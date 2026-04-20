#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--){
        int n,m;cin>>n>>m;
        int r=1;
        for(int i=1;i<=n;++i)r=r*(m-i+1)/i;
        cout<<r<<'\n';
    }
}