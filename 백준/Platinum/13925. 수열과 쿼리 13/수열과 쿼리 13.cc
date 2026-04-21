#include <bits/stdc++.h>
using namespace std;
#define int long long
using p=pair<int,int>;
#define f first
#define s second
const int MOD=1e9+7;
int a[100005];
int tr[400005],lM[400005],lA[400005];
void app(int n,int len,int m,int ad){
    tr[n]=(tr[n]*m+ad*len)%MOD;
    lM[n]=(lM[n]*m)%MOD;
    lA[n]=(lA[n]*m+ad)%MOD;
}
void psh(int n,int s,int e){
    if(lM[n]==1&&lA[n]==0)return;
    int m=(s+e)/2;
    app(n*2,m-s+1,lM[n],lA[n]);
    app(n*2+1,e-m,lM[n],lA[n]);
    lM[n]=1;lA[n]=0;
}
void bld(int n,int s,int e){
    lM[n]=1;
    lA[n]=0;
    if(s==e){
        tr[n]=a[s]%MOD;
        return;
    }
    int m=(s+e)/2;
    bld(n*2,s,m);
    bld(n*2+1,m+1,e);
    tr[n]=(tr[n*2]+tr[n*2+1])%MOD;
}
void upd(int n,int s,int e,int l,int r,int m,int ad){
    if(l>e||r<s)return;
    if(l<=s&&e<=r){
        app(n,e-s+1,m,ad);
        return;
    }
    psh(n,s,e);
    int mid=(s+e)/2;
    upd(n*2,s,mid,l,r,m,ad);
    upd(n*2+1,mid+1,e,l,r,m,ad);
    tr[n]=(tr[n*2]+tr[n*2+1])%MOD;
}
int qry(int n,int s,int e,int l,int r){
    if(l>e||r<s)return 0;
    if(l<=s&&e<=r)return tr[n];
    psh(n,s,e);
    int m=(s+e)/2;
    return (qry(n*2,s,m,l,r)+qry(n*2+1,m+1,e,l,r))%MOD;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;if(!(cin>>n))return 0;
    for(int i=1;i<=n;++i)cin>>a[i];
    bld(1,1,n);
    int m;
    cin>>m;
    while(m--){
        int t,x,y;
        cin>>t>>x>>y;
        if(t==1){
            int v;
            cin>>v;
            upd(1,1,n,x,y,1,v);
        }
        else if(t==2){
            int v;
            cin>>v;
            upd(1,1,n,x,y,v,0);
        }
        else if(t==3){
            int v;
            cin>>v;
            upd(1,1,n,x,y,0,v);
        }
        else cout<<qry(1,1,n,x,y)<<'\n';
    }
    return 0;
}