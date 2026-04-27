#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
const int INF=3e18;
int mn[500005],mx[500005],lset[500005],lseq[500005],ladd[500005],A[100005];
void up(int node){
    mn[node]=min(mn[node*2],mn[node*2+1]);
    mx[node]=max(mx[node*2],mx[node*2+1]);
}
void ap_set(int node,int l,int r,int K){
    mn[node]=mx[node]=K;
    lset[node]=K;
    lseq[node]=INF;
    ladd[node]=0;
}
void ap_seq(int node,int l,int r,int C){
    mn[node]=l+C;
    mx[node]=r+C;
    lseq[node]=C;
    lset[node]=INF;
    ladd[node]=0;
}
void ap_add(int node,int l,int r,int V){
    mn[node]+=V;mx[node]+=V;
    if(lset[node]!=INF)lset[node]+=V;
    else if(lseq[node]!=INF)lseq[node]+=V;
    else ladd[node]+=V;
}
void push(int node,int l,int r){
    int mid=(l+r)/2;
    if(lset[node]!=INF){
        ap_set(node*2,l,mid,lset[node]);
        ap_set(node*2+1,mid+1,r,lset[node]);
        lset[node]=INF;
    }
    else if(lseq[node]!=INF){
        ap_seq(node*2,l,mid,lseq[node]);
        ap_seq(node*2+1,mid+1,r,lseq[node]);
        lseq[node]=INF;
    }
    if(ladd[node]!=0){
        ap_add(node*2,l,mid,ladd[node]);
        ap_add(node*2+1,mid+1,r,ladd[node]);
        ladd[node]=0;
    }
}
void build(int node,int l,int r){
    lset[node]=INF;
    lseq[node]=INF;
    ladd[node]=0;
    if(l==r){
        mn[node]=mx[node]=A[l];
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    up(node);
}
void r_set(int node,int l,int r,int ql,int qr,int K){
    if(ql<=l&&r<=qr){
        ap_set(node,l,r,K);
        return;
    }
    push(node,l,r);
    int mid=(l+r)/2;
    if(ql<=mid)r_set(node*2,l,mid,ql,qr,K);
    if(qr>mid)r_set(node*2+1,mid+1,r,ql,qr,K);
    up(node);
}
void r_seq(int node,int l,int r,int ql,int qr,int C){
    if(ql<=l&&r<=qr){
        ap_seq(node,l,r,C);
        return;
    }
    push(node,l,r);
    int mid=(l+r)/2;
    if(ql<=mid)r_seq(node*2,l,mid,ql,qr,C);
    if(qr>mid)r_seq(node*2+1,mid+1,r,ql,qr,C);
    up(node);
}
void r_add(int node,int l,int r,int ql,int qr,int V){
    if(ql<=l&&r<=qr){
        ap_add(node,l,r,V);
        return;
    }
    push(node,l,r);
    int mid=(l+r)/2;
    if(ql<=mid)r_add(node*2,l,mid,ql,qr,V);
    if(qr>mid)r_add(node*2+1,mid+1,r,ql,qr,V);
    up(node);
}
int isqrt(int x){
    if(x<=0)return 0;
    int r=sqrt(x);
    while((r+1)<=x/(r+1))r++;
    while(r>0&&r>x/r)r--;
    return r;
}
void r_sqrt(int node,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        int smn=isqrt(mn[node]);
        int smx=isqrt(mx[node]);
        if(smn==smx){
            ap_set(node,l,r,smn);
            return;
        }
        if(mx[node]-smx==mn[node]-smn){
            ap_add(node,l,r,smn-mn[node]);
            return;
        }
    }
    push(node,l,r);
    int mid=(l+r)/2;
    if(ql<=mid)r_sqrt(node*2,l,mid,ql,qr);
    if(qr>mid)r_sqrt(node*2+1,mid+1,r,ql,qr);
    up(node);
}
int q_min(int node,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr)return mn[node];
    push(node,l,r);
    int mid=(l+r)/2;
    int res=INF;
    if(ql<=mid)res=min(res,q_min(node*2,l,mid,ql,qr));
    if(qr>mid)res=min(res,q_min(node*2+1,mid+1,r,ql,qr));
    return res;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>A[i];
    build(1,1,n);
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int i;
            cin>>i;
            cout<<q_min(1,1,n,i,i)<<"\n";
        }
        else if(op==2){
            int x,y,t;
            cin>>x>>y>>t;
            if(q_min(1,1,n,x,y)>=t)r_add(1,1,n,x,y,-t);
        }
        else if(op==3){
            int x,y,t;
            cin>>x>>y>>t;
            r_seq(1,1,n,x,y,t-y);
        }
        else if(op==4){
            int x,y;
            cin>>x>>y;
            r_sqrt(1,1,n,x,y);
        }
    }
}