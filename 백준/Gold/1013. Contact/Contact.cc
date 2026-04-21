#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    regex re("(100+1+|01)+");
    while(t--){
        string s;
        cin>>s;
        if(regex_match(s,re))cout<<"YES\n";
        else cout<<"NO\n";
    }
}