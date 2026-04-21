#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF=2e18;
const int MAXN=100005;
struct Node{
    int sum,mn,mx,lz;
} tr[MAXN*4];
int a[MAXN];
void pull(int nd){
    tr[nd].sum=tr[nd*2].sum+tr[nd*2+1].sum;
    tr[nd].mn=min(tr[nd*2].mn,tr[nd*2+1].mn);
    tr[nd].mx=max(tr[nd*2].mx,tr[nd*2+1].mx);
}
void app(int nd,int len,int v){
    tr[nd].sum+=v*len;
    tr[nd].mn+=v;
    tr[nd].mx+=v;
    tr[nd].lz+=v;
}
void push(int nd,int s,int e){
    if(tr[nd].lz){
        int mid=(s+e)/2;
        app(nd*2,mid-s+1,tr[nd].lz);
        app(nd*2+1,e-mid,tr[nd].lz);
        tr[nd].lz=0;
    }
}
void bld(int nd,int s,int e){
    tr[nd].lz=0;
    if(s==e){
        tr[nd].sum=tr[nd].mn=tr[nd].mx=a[s];
        return;
    }
    int mid=(s+e)/2;
    bld(nd*2,s,mid);
    bld(nd*2+1,mid+1,e);
    pull(nd);
}
void add(int nd,int s,int e,int l,int r,int v){
    if(l>e||r<s)return;
    if(l<=s&&e<=r)return app(nd,e-s+1,v);
    push(nd,s,e);
    int mid=(s+e)/2;
    add(nd*2,s,mid,l,r,v);
    add(nd*2+1,mid+1,e,l,r,v);
    pull(nd);
}
int fdiv(int v,int d){
    if(v>=0)return v/d;
    return (v-d+1)/d;
}
void udiv(int nd,int s,int e,int l,int r,int d){
    if(l>e||r<s)return;
    if(l<=s&&e<=r){
        int d1=tr[nd].mn-fdiv(tr[nd].mn,d);
        int d2=tr[nd].mx-fdiv(tr[nd].mx,d);
        if(d1==d2)return app(nd,e-s+1,-d1);
    }
    push(nd,s,e);
    int mid=(s+e)/2;
    udiv(nd*2,s,mid,l,r,d);
    udiv(nd*2+1,mid+1,e,l,r,d);
    pull(nd);
}
int qmn(int nd,int s,int e,int l,int r){
    if(l>e||r<s)return INF;
    if(l<=s&&e<=r)return tr[nd].mn;
    push(nd,s,e);
    int mid=(s+e)/2;
    return min(qmn(nd*2,s,mid,l,r),qmn(nd*2+1,mid+1,e,l,r));
}
int qsum(int nd,int s,int e,int l,int r){
    if(l>e||r<s)return 0;
    if(l<=s&&e<=r)return tr[nd].sum;
    push(nd,s,e);
    int mid=(s+e)/2;
    return qsum(nd*2,s,mid,l,r)+qsum(nd*2+1,mid+1,e,l,r);
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;++i)cin>>a[i];
    bld(1,1,n);
    while(q--){
        int t,l,r;cin>>t>>l>>r;
        l++;r++;
        if(t==1){
            int c;cin>>c;
            add(1,1,n,l,r,c);
        }else if(t==2){
            int d;cin>>d;
            udiv(1,1,n,l,r,d);
        }else if(t==3) cout<<qmn(1,1,n,l,r)<<'\n';
        else cout<<qsum(1,1,n,l,r)<<'\n';
    }
    return 0;
}