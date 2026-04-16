#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF=1e18;

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    while(cin>>n>>m&&(n||m)){
        int S,D;
        cin>>S>>D;
        vector<tuple<int,int,int>> g[n],rg[n];
        vector<bool> removed(m,false);
        for(int i=0;i<m;i++){
            int u,v,w; cin>>u>>v>>w;
            g[u].push_back({v,w,i});
            rg[v].push_back({u,w,i});
        }
        auto dijk=[&](int src,vector<tuple<int,int,int>>* gr,bool useRemoved)->vector<int>{
            vector<int> d(n,INF);
            priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
            d[src]=0; pq.push({0,src});
            while(!pq.empty()){
                auto [c,u]=pq.top(); pq.pop();
                if(c>d[u]) continue;
                for(auto [v,w,i]:gr[u]){
                    if(useRemoved&&removed[i]) continue;
                    if(d[u]+w<d[v]){
                        d[v]=d[u]+w;
                        pq.push({d[v],v});
                    }
                }
            }
            return d;
        };
        vector<int> ds=dijk(S,g,false);
        vector<bool> vis(n,false);
        queue<int> q;
        q.push(D); vis[D]=true;
        while(!q.empty()){
            int v=q.front(); q.pop();
            for(auto [u,w,i]:rg[v]){
                if(ds[u]+w==ds[v]){
                    removed[i]=true;
                    if(!vis[u]){
                        vis[u]=true;
                        q.push(u);
                    }
                }
            }
        }
        vector<int> ans=dijk(S,g,true);
        cout<<(ans[D]==INF?-1:ans[D])<<'\n';
    }
}