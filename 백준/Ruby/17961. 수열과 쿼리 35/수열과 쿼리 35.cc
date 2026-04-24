#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
const int INF=1e18;
int lc[120005],rc[120005],v[120005],mn[120005],mx[120005];
int lv[120005],rv[120005],sz[120005],prio[120005],ans[120005];
int rt;
int glg(int u,int V){
    if(!u||mx[u]<=V)return INF;
    int res=glg(rc[u],V);
    if(res!=INF)return res;
    if(v[u]>V)return v[u];
    return glg(lc[u],V);
}
int gfl(int u,int V){
    if(!u||mn[u]>=V)return -INF;
    int res=gfl(lc[u],V);
    if(res!=-INF)return res;
    if(v[u]<V)return v[u];
    return gfl(rc[u],V);
}
void up(int u){
    if(!u)return;
    int l=lc[u],r=rc[u];
    mn[u]=mx[u]=v[u];
    if(l)mn[u]=min(mn[u],mn[l]),mx[u]=max(mx[u],mx[l]);
    if(r)mn[u]=min(mn[u],mn[r]),mx[u]=max(mx[u],mx[r]);
    sz[u]=1+sz[l]+sz[r];
    ans[u]=ans[l]|ans[r];
    if(lv[l]<v[u])ans[u]=1;
    if(v[u]<rv[r])ans[u]=1;
    if(lv[l]<mx[r])ans[u]=1;
    if(mn[l]<rv[r])ans[u]=1;
    if(mn[l]<v[u]&&v[u]<mx[r])ans[u]=1;
    lv[u]=min(lv[l],lv[r]);
    if(mn[l]<v[u])lv[u]=min(lv[u],v[u]);
    if(v[u]<mx[r])lv[u]=min(lv[u],glg(r,v[u]));
    if(mn[l]<mx[r])lv[u]=min(lv[u],glg(r,mn[l]));
    rv[u]=max(rv[l],rv[r]);
    if(mn[l]<v[u])rv[u]=max(rv[u],gfl(l,v[u]));
    if(v[u]<mx[r])rv[u]=max(rv[u],v[u]);
    if(mn[l]<mx[r])rv[u]=max(rv[u],gfl(l,mx[r]));
}
void sp(int u,int k,int&x,int&y){
    if(!u){x=y=0;return;}
    if(sz[lc[u]]<k){
        x=u;
        sp(rc[u],k-sz[lc[u]]-1,rc[u],y);
    }else{
        y=u;
        sp(lc[u],k,x,lc[u]);
    }
    up(u);
}
void mg(int&u,int x,int y){
    if(!x||!y){u=x?x:y;return;}
    if(prio[x]>prio[y]){
        u=x;
        mg(rc[u],rc[x],y);
    }else{
        u=y;
        mg(lc[u],x,lc[y]);
    }
    up(u);
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    mn[0]=INF;mx[0]=-INF;lv[0]=INF;rv[0]=-INF;ans[0]=0;sz[0]=0;
    int n;
    cin>>n;
    mt19937 rng(1337);
    for(int i=1;i<=n;++i){
        cin>>v[i];
        mn[i]=mx[i]=v[i];
        lv[i]=INF;rv[i]=-INF;ans[i]=0;sz[i]=1;
        prio[i]=rng();
        mg(rt,rt,i);
    }
    int m;
    cin>>m;
    while(m--){
        int L,R,K;
        cin>>L>>R>>K;
        int a,b,c;
        sp(rt,L-1,a,b);
        sp(b,R-L+1,b,c);
        K%=(R-L+1);
        if(K>0){
            int m1,m2;
            sp(b,(R-L+1)-K,m1,m2);
            mg(b,m2,m1);
        }
        mg(rt,a,b);
        mg(rt,rt,c);
        if(ans[rt])cout<<"YES\n";
        else cout<<"NO\n";
    }
}