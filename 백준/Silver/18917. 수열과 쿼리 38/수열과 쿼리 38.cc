#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p = pair<int,int>;
#define f first
#define s second

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int m;cin>>m;
    int sum=0,xr=0;
    while(m--){
        int op;cin>>op;
        if(op<=2){
            int v;cin>>v;
            if(op==1)sum+=v;
            else sum-=v;
            xr^=v;
        }else if(op==3)cout<<sum<<"\n";
        else cout<<xr<<"\n";
    }
}