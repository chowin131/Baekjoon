#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
const int MOD=1e9+7;
int n,k,h[505],c[505][505];

vector<int> solve(int l,int r,int ph){
    if(l>r) return {1};
    int m=l;
    for(int i=l+1;i<=r;i++) if(h[i]<h[m]) m=i;
    int cur_h=(h[m]-ph)%MOD;
    if(cur_h<0) cur_h+=MOD;
    auto l_dp=solve(l,m-1,h[m]);
    auto r_dp=solve(m+1,r,h[m]);
    int w=r-l+1;
    int mx=min(w,k);
    vector<int> tmp(mx+1,0);
    for(int i=0;i<l_dp.size();i++) for(int j=0;j<r_dp.size();j++) if(i+j<=mx) tmp[i+j]=(tmp[i+j]+l_dp[i]*r_dp[j])%MOD;
    vector<int> p_arr(mx+1,0);
    p_arr[0]=1;
    for(int i=1;i<=mx;i++) p_arr[i]=(p_arr[i-1]*((cur_h-i+1)%MOD+MOD)%MOD)%MOD;
    vector<int> dp(mx+1,0);
    for(int i=0;i<=mx;i++) for(int j=0;j<=i;j++){
        int idx=i-j;
        if(idx<tmp.size()&&tmp[idx]&&p_arr[j]&&c[w-idx][j]){
            int w_=(tmp[idx]*p_arr[j])%MOD;
            w_=(w_*c[w-idx][j])%MOD;
            dp[i]=(dp[i]+w_)%MOD;
        }
    }
    return dp;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>h[i];
    if(k>n){
        cout<<0;
        return 0;
    }
    for(int i=0;i<=n;i++){
        c[i][0]=1;
        for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
    }
    auto ans=solve(1,n,0);
    if(k<ans.size()) cout<<ans[k];
    else cout<<0;
}