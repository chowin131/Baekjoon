#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF=1e18;
struct Line{
    int a,b;
    int eval(int x) const{return a*x+b;}
};
struct Node{
    int mn1,mn2,mnc,laz,fail;
    Line sum,lmax,rmax,tmax;
}tree[400005];
int A[100005];
int div_ceil(int a,int b){
    int res=a/b;
    int rem=a%b;
    if(rem!=0&&((a<0)==(b<0))) res++;
    return res;
}
void pull(int node){
    int lc=node*2,rc=node*2+1;
    if(tree[lc].mn1==tree[rc].mn1){
        tree[node].mn1=tree[lc].mn1;
        tree[node].mn2=min(tree[lc].mn2,tree[rc].mn2);
        tree[node].mnc=tree[lc].mnc+tree[rc].mnc;
    }
    else if(tree[lc].mn1<tree[rc].mn1){
        tree[node].mn1=tree[lc].mn1;
        tree[node].mn2=min(tree[lc].mn2,tree[rc].mn1);
        tree[node].mnc=tree[lc].mnc;
    }
    else{
        tree[node].mn1=tree[rc].mn1;
        tree[node].mn2=min(tree[lc].mn1,tree[rc].mn2);
        tree[node].mnc=tree[rc].mnc;
    }
    int x=tree[node].mn1;
    tree[node].fail=min(tree[lc].fail,tree[rc].fail);
    auto get_line=[&](int child,Line L)->Line{
        if(tree[child].mn1==x) return L;
        return {0,L.a*tree[child].mn1+L.b};
    };
    Line L_sum=get_line(lc,tree[lc].sum);
    Line R_sum=get_line(rc,tree[rc].sum);
    Line L_lmax=get_line(lc,tree[lc].lmax);
    Line R_lmax=get_line(rc,tree[rc].lmax);
    Line L_rmax=get_line(lc,tree[lc].rmax);
    Line R_rmax=get_line(rc,tree[rc].rmax);
    Line L_tmax=get_line(lc,tree[lc].tmax);
    Line R_tmax=get_line(rc,tree[rc].tmax);
    tree[node].sum={L_sum.a+R_sum.a,L_sum.b+R_sum.b};
    Line c_lmax[]={L_lmax,{L_sum.a+R_lmax.a,L_sum.b+R_lmax.b}};
    Line c_rmax[]={R_rmax,{R_sum.a+L_rmax.a,R_sum.b+L_rmax.b}};
    Line c_tmax[]={L_tmax,R_tmax,{L_rmax.a+R_lmax.a,L_rmax.b+R_lmax.b}};
    auto cmp=[&](Line A,Line B){
        int va=A.a*x+A.b;
        int vb=B.a*x+B.b;
        if(va!=vb) return va<vb;
        return A.a<B.a;
    };
    tree[node].lmax=c_lmax[0];
    if(cmp(tree[node].lmax,c_lmax[1])) tree[node].lmax=c_lmax[1];
    tree[node].rmax=c_rmax[0];
    if(cmp(tree[node].rmax,c_rmax[1])) tree[node].rmax=c_rmax[1];
    tree[node].tmax=c_tmax[0];
    for(int i=1;i<3;i++) if(cmp(tree[node].tmax,c_tmax[i])) tree[node].tmax=c_tmax[i];
    auto update_fail=[&](Line best,Line cand){
        if(cand.a<=best.a) return;
        int num=best.b-cand.b;
        int den=cand.a-best.a;
        int inter=div_ceil(num,den);
        if(inter<tree[node].fail) tree[node].fail=inter;
    };
    update_fail(tree[node].lmax,c_lmax[0]);
    update_fail(tree[node].lmax,c_lmax[1]);
    update_fail(tree[node].rmax,c_rmax[0]);
    update_fail(tree[node].rmax,c_rmax[1]);
    update_fail(tree[node].tmax,c_tmax[0]);
    update_fail(tree[node].tmax,c_tmax[1]);
    update_fail(tree[node].tmax,c_tmax[2]);
}
void apply(int node,int x){
    if(tree[node].mn1>=x) return;
    tree[node].mn1=x;
    tree[node].laz=x;
}
void push(int node){
    if(tree[node].laz!=-INF){
        apply(node*2,tree[node].laz);
        apply(node*2+1,tree[node].laz);
        tree[node].laz=-INF;
    }
}
void build(int node,int l,int r){
    tree[node].laz=-INF;
    if(l==r){
        tree[node].mn1=A[l];
        tree[node].mn2=INF;
        tree[node].mnc=1;
        tree[node].fail=INF;
        tree[node].sum={1,0};
        tree[node].lmax={1,0};
        tree[node].rmax={1,0};
        tree[node].tmax={1,0};
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    pull(node);
}
void update(int node,int l,int r,int ql,int qr,int x){
    if(qr<l||r<ql||tree[node].mn1>=x) return;
    if(ql<=l&&r<=qr&&x<tree[node].mn2&&x<tree[node].fail){
        apply(node,x);
        return;
    }
    push(node);
    int mid=(l+r)/2;
    update(node*2,l,mid,ql,qr,x);
    update(node*2+1,mid+1,r,ql,qr,x);
    pull(node);
}
struct NodeResult{
    int sum,lmax,rmax,tmax;
};
NodeResult get_res(int node){
    int x=tree[node].mn1;
    return {tree[node].sum.eval(x),tree[node].lmax.eval(x),tree[node].rmax.eval(x),tree[node].tmax.eval(x)};
}
NodeResult merge_res(NodeResult L,NodeResult R){
    NodeResult res;
    res.sum=L.sum+R.sum;
    res.lmax=max(L.lmax,L.sum+R.lmax);
    res.rmax=max(R.rmax,R.sum+L.rmax);
    res.tmax=max({L.tmax,R.tmax,L.rmax+R.lmax});
    return res;
}
NodeResult query(int node,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr) return get_res(node);
    push(node);
    int mid=(l+r)/2;
    if(qr<=mid) return query(node*2,l,mid,ql,qr);
    if(ql>mid) return query(node*2+1,mid+1,r,ql,qr);
    return merge_res(query(node*2,l,mid,ql,qr),query(node*2+1,mid+1,r,ql,qr));
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>A[i];
    }
    build(1,1,n);
    while(q--){
        int type;
        cin>>type;
        if(type==0){
            int l,r,x;
            cin>>l>>r>>x;
            update(1,1,n,l,r,x);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<max(0LL,query(1,1,n,l,r).tmax)<<"\n";
        }
    }
}