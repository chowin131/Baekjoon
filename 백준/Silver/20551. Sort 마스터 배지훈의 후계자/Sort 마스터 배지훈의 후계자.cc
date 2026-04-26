#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<int> a(n);
    for(int i=0;i<n;++i) cin>>a[i];
    sort(a.begin(),a.end());
    while(m--){
        int d;
        cin>>d;
        int idx=lower_bound(a.begin(),a.end(),d)-a.begin();
        if(idx<n&&a[idx]==d) cout<<idx<<"\n";
        else cout<<"-1\n";
    }
}