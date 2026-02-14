#include <bits/stdc++.h>
using namespace std;
main(){
    ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
    int w,h;
    cin>>w>>h;
    int n,d;
    cin>>n>>d;
    vector<int> a(n+1),p(n+1);
    a[0]=0;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>p[i];
    int ans=INT_MAX;
    for(int k=1;k<=n;k++){
        int cost=w*p[k];
        for(int i=1;i<k;i++) cost+=(a[i]-a[i-1])*p[i];
        int lo=min(d,a[k-1]),hi=max(d,a[k-1]);
        for(int i=1;i<=n&&a[i-1]<hi;i++){
            int L=max(a[i-1],lo),R=min(a[i],hi);
            if(L<R) cost+=(R-L)*p[i];
        }
        ans=min(ans,cost);
    }
    cout<<ans;
}