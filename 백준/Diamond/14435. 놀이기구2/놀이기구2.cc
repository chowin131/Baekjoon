#include <bits/stdc++.h>
using namespace std;
#define int long
const int M=200005;
int n,m,kk,q,lim[M],kid[M],qi[M],qj[M],qk[M],h[M],ti[M],tj[M],ans[M],cur,valid[M],i;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq[M];
inline void add(int idx){
    int u=qi[idx],v=qj[idx],L=lim[qk[idx]];
    int half=(L-h[u]-h[v]+1)/2;
    ti[idx]=h[u]+half;
    tj[idx]=h[v]+half;
    pq[u].push({ti[idx],idx});
    pq[v].push({tj[idx],idx});
}
main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>kk>>q;
    for(i=1;i<=m;i++) cin>>lim[i];
    for(i=1;i<=kk;i++) cin>>kid[i];
    for(i=1;i<=q;add(i++)) cin>>qi[i]>>qj[i]>>qk[i];
    for(i=1;i<=kk;i++){
        int g=((i>2&&ans[i-1]>ans[i-2])?2:1);
        int x=kid[i];
        h[x]+=g;
        while(!pq[x].empty()&&pq[x].top().first<=h[x]){
            auto[t,idx]=pq[x].top();pq[x].pop();
            if(valid[idx]) continue;
            if(x==qi[idx]&&t!=ti[idx]) continue;
            if(x==qj[idx]&&t!=tj[idx]) continue;
            if(h[qi[idx]]+h[qj[idx]]>=lim[qk[idx]]) valid[idx]=1,cur++;
            else add(idx);
        }
        ans[i]=cur;
        cout<<cur<<"\n";
    }
}