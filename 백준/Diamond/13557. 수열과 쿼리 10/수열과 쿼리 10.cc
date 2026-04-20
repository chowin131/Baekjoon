#include <bits/stdc++.h>
using namespace std;
#define int long long
using p=pair<int,int>;
#define f first
#define s second

const int MIN_INF=-1e15;

struct Nd{int sum,lmax,rmax,amax;};

Nd mg(Nd L,Nd R){
    if(L.amax==MIN_INF)return R;
    if(R.amax==MIN_INF)return L;
    Nd res;
    res.sum=L.sum+R.sum;
    res.lmax=max(L.lmax,L.sum+R.lmax);
    res.rmax=max(R.rmax,R.sum+L.rmax);
    res.amax=max({L.amax,R.amax,L.rmax+R.lmax});
    return res;
}

const int MAXN=100005;
int A[MAXN];
Nd tr[MAXN*4];

void bld(int nd,int s,int e){
    if(s==e){
        tr[nd]={A[s],A[s],A[s],A[s]};
        return;
    }
    int mid=(s+e)/2;
    bld(nd*2,s,mid);
    bld(nd*2+1,mid+1,e);
    tr[nd]=mg(tr[nd*2],tr[nd*2+1]);
}

Nd qry(int nd,int s,int e,int l,int r){
    if(l>e||r<s||l>r)return {0,MIN_INF,MIN_INF,MIN_INF};
    if(l<=s&&e<=r)return tr[nd];
    int mid=(s+e)/2;
    Nd L=qry(nd*2,s,mid,l,r);
    Nd R=qry(nd*2+1,mid+1,e,l,r);
    return mg(L,R);
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>A[i];
    bld(1,1,n);
    int m;cin>>m;
    while(m--){
        int x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
        if(y1<x2){
            Nd L=qry(1,1,n,x1,y1);
            Nd M=qry(1,1,n,y1+1,x2-1);
            Nd R=qry(1,1,n,x2,y2);
            cout<<L.rmax+M.sum+R.lmax<<'\n';
        }else{
            Nd A_nd=qry(1,1,n,x1,x2-1);
            Nd B_nd=qry(1,1,n,x2,y1);
            Nd C_nd=qry(1,1,n,y1+1,y2);
            int a1=A_nd.rmax+B_nd.lmax;
            int a2=B_nd.rmax+C_nd.lmax;
            int a3=A_nd.rmax+B_nd.sum+C_nd.lmax;
            int a4=B_nd.amax;
            cout<<max({a1,a2,a3,a4})<<'\n';
        }
    }
    return 0;
}