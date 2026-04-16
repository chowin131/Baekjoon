#include <bits/stdc++.h>
#define int long long
using namespace std;

struct MCMF {
    struct Edge { int to,cap,cost,rev; };
    vector<vector<Edge>> g;
    MCMF(int n): g(n){}
    void add(int u,int v,int cap,int cost){
        g[u].push_back({v,cap,cost,(int)g[v].size()});
        g[v].push_back({u,0,-cost,(int)g[u].size()-1});
    }
    pair<int,int> run(int s,int t){
        int flow=0,cost=0,n=g.size();
        while(true){
            vector<int> d(n,2e9),inq(n,0),pv(n,-1),pe(n,-1);
            d[s]=0; queue<int> q; q.push(s); inq[s]=1;
            while(!q.empty()){
                int u=q.front(); q.pop(); inq[u]=0;
                for(int i=0;i<(int)g[u].size();i++){
                    auto& e=g[u][i];
                    if(e.cap>0&&d[u]+e.cost<d[e.to]){
                        d[e.to]=d[u]+e.cost;
                        pv[e.to]=u; pe[e.to]=i;
                        if(!inq[e.to]){inq[e.to]=1;q.push(e.to);}
                    }
                }
            }
            if(d[t]>=2e9) break;
            int f=2e9;
            for(int v=t;v!=s;v=pv[v]) f=min(f,g[pv[v]][pe[v]].cap);
            for(int v=t;v!=s;v=pv[v]){
                g[pv[v]][pe[v]].cap-=f;
                g[v][g[pv[v]][pe[v]].rev].cap+=f;
            }
            flow+=f; cost+=f*d[t];
        }
        return {flow,cost};
    }
};

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n,m; cin>>n>>m;
    MCMF mcmf(n+m+2);
    int S=0,T=n+m+1;
    for(int j=1;j<=n;j++){
        int a;
        cin>>a;
        mcmf.add(j,T,a,0);
    }
    for(int i=1;i<=m;i++){
        int b;
        cin>>b;
        mcmf.add(S,n+i,b,0);
    }
    vector<vector<int>> C(m+1,vector<int>(n+1));
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) cin>>C[i][j];
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++){
        int d;
        cin>>d;
        mcmf.add(n+i,j,C[i][j],d);
    }
    auto [flow,cost]=mcmf.run(S,T);
    cout<<flow<<'\n'<<cost<<'\n';
}