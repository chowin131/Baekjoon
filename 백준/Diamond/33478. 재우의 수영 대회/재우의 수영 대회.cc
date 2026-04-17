#include <bits/stdc++.h>
using namespace std;
main(){
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--){
        long double a,b,c,s,ans;
        cin>>a>>b>>c;
        s=(a+b+c)/2;
        ans=sqrt((s-a)/s*(s-b)*(s-c))/2;
        cout<<fixed<<setprecision(10)<<ans<<"\n";
    }
}