#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN=40001,LOG=16;
vector<pair<int,int>> g[MAXN];
int par[MAXN][LOG],dep[MAXN];
int d[MAXN];

void dfs(int u,int p,int depth,int dist){
    par[u][0]=p; dep[u]=depth; d[u]=dist;
    for(auto [v,w]:g[u]) if(v!=p)
        dfs(v,u,depth+1,dist+w);
}

int lca(int u,int v){
    if(dep[u]<dep[v]) swap(u,v);
    int diff=dep[u]-dep[v];
    for(int i=0;i<LOG;i++) if((diff>>i)&1) u=par[u][i];
    if(u==v) return u;
    for(int i=LOG-1;i>=0;i--)
        if(par[u][i]!=par[v][i]){u=par[u][i];v=par[v][i];}
    return par[u][0];
}

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n; cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v,w; cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    dfs(1,0,0,0);
    for(int j=1;j<LOG;j++)
        for(int i=1;i<=n;i++)
            par[i][j]=par[par[i][j-1]][j-1];
    int m; cin>>m;
    while(m--){
        int u,v; cin>>u>>v;
        int l=lca(u,v);
        cout<<d[u]+d[v]-2*d[l]<<'\n';
    }
}