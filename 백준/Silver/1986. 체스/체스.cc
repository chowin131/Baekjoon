#include <bits/stdc++.h>
using namespace std;
#define int long long
using p=pair<int,int>;
#define f first
#define s second
int a[1005][1005];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    int q;
    cin>>q;
    vector<p> Q;
    for(int i=0;i<q;++i){
        int r,c;cin>>r>>c;
        Q.push_back({r,c});
        a[r][c]=1;
    }
    int k;cin>>k;
    vector<p> K;
    for(int i=0;i<k;++i){
        int r,c;cin>>r>>c;
        K.push_back({r,c});
        a[r][c]=1;
    }
    int w;cin>>w;
    for(int i=0;i<w;++i){
        int r,c;cin>>r>>c;
        a[r][c]=1;
    }
    int dx[]={-2,-2,-1,-1,1,1,2,2},dy[]={-1,1,-2,2,-2,2,-1,1};
    for(auto x:K)
        for(int i=0;i<8;++i){
            int nr=x.f+dx[i],nc=x.s+dy[i];
            if(1<=nr&&nr<=n&&1<=nc&&nc<=m)if(a[nr][nc]==0)a[nr][nc]=2;
        }
    int qx[]={-1,-1,-1,0,0,1,1,1},qy[]={-1,0,1,-1,1,-1,0,1};
    for(auto x:Q)
        for(int i=0;i<8;++i){
            int nr=x.f+qx[i],nc=x.s+qy[i];
            while(1<=nr&&nr<=n&&1<=nc&&nc<=m){
                if(a[nr][nc]==1)break;
                a[nr][nc]=2;
                nr+=qx[i];
                nc+=qy[i];
            }
        }
    int ans=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(a[i][j]==0)ans++;
    cout<<ans;
}