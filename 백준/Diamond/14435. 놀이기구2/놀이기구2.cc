#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN=200005;
int n,m,k_days,q;
int lim[MAXN],kid[MAXN];
int qi[MAXN],qj[MAXN],qk[MAXN];
int h[MAXN],ti[MAXN],tj[MAXN];
bool valid[MAXN];
int ans[MAXN],cur=0;

priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq[MAXN];

void add(int idx){
    int u=qi[idx],v=qj[idx],L=lim[qk[idx]];
    int half=(L-h[u]-h[v]+1)/2;
    ti[idx]=h[u]+half;
    tj[idx]=h[v]+half;
    pq[u].push({ti[idx],idx});
    pq[v].push({tj[idx],idx});
}

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>k_days>>q;
    for(int i=1;i<=m;i++) cin>>lim[i];
    for(int i=1;i<=k_days;i++) cin>>kid[i];
    for(int i=1;i<=q;add(i++)) cin>>qi[i]>>qj[i]>>qk[i];
    for(int d=1;d<=k_days;d++){
        int g=((d>2&&ans[d-1]>ans[d-2])?2:1);
        int x=kid[d];
        h[x]+=g;
        while(!pq[x].empty()&&pq[x].top().first<=h[x]){
            auto[t,idx]=pq[x].top(); pq[x].pop();
            if(valid[idx]) continue;
            if(x==qi[idx]&&t!=ti[idx]) continue;
            if(x==qj[idx]&&t!=tj[idx]) continue;
            int u=qi[idx],v=qj[idx];
            if(h[u]+h[v]>=lim[qk[idx]]) valid[idx]=true,cur++;
            else add(idx);
        }
        ans[d]=cur;
        cout<<cur<<"\n";
    }
}