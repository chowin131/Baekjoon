#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int t;cin>>t;
    while(t--){
        string s;int n;cin>>s>>n;
        int c1=s[0]-'A',r1=s[1]-'1';
        int c2=(n-1)%8,r2=(n-1)/8;
        if((c1+r1)%2==(c2+r2)%2)cout<<"YES\n";
        else cout<<"NO\n";
    }
}