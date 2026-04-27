#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;++i) cin>>a[i];
    for(int i=0;i<n;++i) cin>>b[i];
    sort(a.begin(),a.end());
    sort(b.rbegin(),b.rend());
    int ans=0;
    for(int i=0;i<n;++i) ans+=a[i]*b[i];
    cout<<ans;
}