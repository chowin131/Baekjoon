#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p = pair<int,int>;
#define f first
#define s second
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int tc;
    cin>>tc;
    while(tc--){
        int n;
        cin>>n;
        int k=(2*n+1)/3;
        cout<<k<<"\n";
        int o=min(k,n-k+1);
        int e=k-o;
        int r=n-k+1;
        for(int i=1;i<=o;++i){
            cout<<r<<" "<<2*i-1<<"\n";
            r++;
        }
        for(int i=1;i<=e;++i){
            cout<<r<<" "<<2*i<<"\n";
            r++;
        }
    }
}