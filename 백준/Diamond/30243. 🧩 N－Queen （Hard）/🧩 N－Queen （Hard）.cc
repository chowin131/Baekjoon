#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
int n,q[35],ans[35],c,d1,d2,m,er[35],vis[35];
int dfs(int d){
    if(d==m)return 1;
    int idx=-1,mc=99,r;
    for(int i=0;i<m;++i){
        if(vis[i])continue;
        int row=er[i],cnt=0;
        for(int j=1;j<=n;++j)if(!((c>>j&1)||(d1>>(row+j)&1)||(d2>>(row-j+n)&1)))cnt++;
        if(cnt<mc)mc=cnt,idx=i,r=row;
    }
    if(mc==0)return 0;
    vis[idx]=1;
    for(int j=1;j<=n;++j){
        if((c>>j&1)||(d1>>(r+j)&1)||(d2>>(r-j+n)&1))continue;
        c|=1ll<<j;d1|=1ll<<(r+j);d2|=1ll<<(r-j+n);
        ans[r]=j;
        if(dfs(d+1))return 1;
        c^=1ll<<j;d1^=1ll<<(r+j);d2^=1ll<<(r-j+n);
    }
    vis[idx]=0;
    return 0;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>q[i];
        if(q[i]){
            c|=1ll<<q[i];d1|=1ll<<(i+q[i]);d2|=1ll<<(i-q[i]+n);ans[i]=q[i];
        }
        else er[m++]=i;
    }
    if(dfs(0)) for(int i=1;i<=n;++i) cout<<ans[i]<<" ";
    else cout<<-1;
}