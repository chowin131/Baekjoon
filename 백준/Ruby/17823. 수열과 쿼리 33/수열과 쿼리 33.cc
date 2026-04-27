#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
const int INF=1e18;
struct Seq{
    int st;
    vector<int> v;
};
void make_concave(Seq& q){
    if(q.st==-1||q.v.empty()) return;
    vector<p> pts;
    for(int i=0;i<(int)q.v.size();++i)
        if(q.v[i]>-INF/2) pts.push_back({i,q.v[i]});
    if(pts.empty()){
        q.st=-1;
        q.v.clear();
        return;
    }
    vector<p> h;
    for(auto pt:pts){
        while(h.size()>=2){
            p p1=h[h.size()-2],p2=h[h.size()-1];
            int dy1=p2.s-p1.s,dx1=p2.f-p1.f;
            int dy2=pt.s-p2.s,dx2=pt.f-p2.f;
            if(dy1*dx2<=dy2*dx1) h.pop_back();
            else break;
        }
        h.push_back(pt);
    }
    int nst=h[0].f,ned=h.back().f;
    vector<int> nv(ned-nst+1);
    nv[0]=h[0].s;
    int idx=0;
    for(int i=1;i<(int)h.size();++i){
        int dx=h[i].f-h[i-1].f,dy=h[i].s-h[i-1].s;
        int quo=dy>=0?dy/dx:(dy-dx+1)/dx,rem=dy-quo*dx;
        for(int j=0;j<dx;++j){
            idx++;
            nv[idx]=nv[idx-1]+quo+(j<rem?1:0);
        }
    }
    q.st+=nst;
    q.v=nv;
}
Seq merge_seq(const Seq& A,const Seq& B,bool bm){
    if(A.st==-1||B.st==-1) return {-1,{}};
    Seq C;
    C.st=A.st+B.st-(bm?1:0);
    C.v.assign(A.v.size()+B.v.size()-1,-INF);
    C.v[0]=A.v[0]+B.v[0];
    int n=A.v.size(),m=B.v.size(),i=1,j=1,idx=1;
    while(i<n&&j<m){
        int dA=A.v[i]-A.v[i-1],dB=B.v[j]-B.v[j-1];
        if(dA>dB){C.v[idx]=C.v[idx-1]+dA;i++;}
        else{C.v[idx]=C.v[idx-1]+dB;j++;}
        idx++;
    }
    while(i<n){C.v[idx]=C.v[idx-1]+(A.v[i]-A.v[i-1]);i++;idx++;}
    while(j<m){C.v[idx]=C.v[idx-1]+(B.v[j]-B.v[j-1]);j++;idx++;}
    return C;
}
void update_max(Seq& t,const Seq& src){
    if(src.st==-1) return;
    if(t.st==-1){t=src;return;}
    int mn=min(t.st,src.st);
    int mx=max(t.st+(int)t.v.size()-1,src.st+(int)src.v.size()-1);
    vector<int> nv(mx-mn+1,-INF);
    for(int i=0;i<(int)t.v.size();++i){
        int k=t.st+i;
        nv[k-mn]=max(nv[k-mn],t.v[i]);
    }
    for(int i=0;i<(int)src.v.size();++i){
        int k=src.st+i;
        nv[k-mn]=max(nv[k-mn],src.v[i]);
    }
    t.st=mn;
    t.v=nv;
}

struct Node{
    Seq sq[4];
    vector<int> df[4];
};
void compute_diff(Node& u){
    for(int m=0;m<4;++m){
        if(u.sq[m].st==-1||u.sq[m].v.empty()) continue;
        int sz=u.sq[m].v.size();
        u.df[m].resize(sz-1);
        for(int i=0;i<sz-1;++i) u.df[m][i]=u.sq[m].v[i+1]-u.sq[m].v[i];
    }
}
Node merge_node(const Node& L,const Node& R){
    Node C;
    for(int i=0;i<4;++i) C.sq[i].st=-1;
    for(int bL=0;bL<4;++bL){
        if(L.sq[bL].st==-1) continue;
        for(int bR=0;bR<4;++bR){
            if(R.sq[bR].st==-1) continue;
            int Ll=bL&1,Lr=(bL>>1)&1,Rl=bR&1,Rr=(bR>>1)&1;
            int m=Ll|(Rr<<1);
            update_max(C.sq[m],merge_seq(L.sq[bL],R.sq[bR],false));
            if(Lr==1&&Rl==1) update_max(C.sq[m],merge_seq(L.sq[bL],R.sq[bR],true));
        }
    }
    for(int i=0;i<4;++i) make_concave(C.sq[i]);
    return C;
}
Node make_leaf(int x){
    Node u;
    for(int i=0;i<4;++i) u.sq[i].st=-1;
    u.sq[0].st=0;u.sq[0].v={0};
    u.sq[3].st=1;u.sq[3].v={x};
    compute_diff(u);
    return u;
}

const int MAXN=35005;
Node tree[4*MAXN];
int arr[MAXN];

void build(int node,int start,int end){
    if(start==end){tree[node]=make_leaf(arr[start]);return;}
    int mid=(start+end)/2;
    build(2*node,start,mid);
    build(2*node+1,mid+1,end);
    tree[node]=merge_node(tree[2*node],tree[2*node+1]);
    compute_diff(tree[node]);
}
struct State{int v,c;};
struct EvalNode{
    State dp[4];
    EvalNode(){for(int i=0;i<4;++i) dp[i]={-INF,-INF};}
};
EvalNode evaluate(const Node& u,int lam){
    EvalNode res;
    for(int m=0;m<4;++m){
        if(u.sq[m].st==-1) continue;
        int pk=0;
        if(!u.df[m].empty()){
            auto it=upper_bound(u.df[m].begin(),u.df[m].end(),lam,greater<int>());
            pk=distance(u.df[m].begin(),it);
        }
        int c=u.sq[m].st+pk,sum=u.sq[m].v[pk];
        res.dp[m]={sum-lam*c,c};
    }
    return res;
}
EvalNode merge_eval(const EvalNode& L,const EvalNode& R,int lam){
    EvalNode C;
    for(int bL=0;bL<4;++bL){
        if(L.dp[bL].v<=-INF/2) continue;
        for(int bR=0;bR<4;++bR){
            if(R.dp[bR].v<=-INF/2) continue;
            int Ll=bL&1,Lr=(bL>>1)&1,Rl=bR&1,Rr=(bR>>1)&1;
            int m=Ll|(Rr<<1);
            int v1=L.dp[bL].v+R.dp[bR].v,c1=L.dp[bL].c+R.dp[bR].c;
            if(v1>C.dp[m].v||(v1==C.dp[m].v&&c1>C.dp[m].c)) C.dp[m]={v1,c1};
            if(Lr==1&&Rl==1){
                int v2=L.dp[bL].v+R.dp[bR].v+lam,c2=L.dp[bL].c+R.dp[bR].c-1;
                if(v2>C.dp[m].v||(v2==C.dp[m].v&&c2>C.dp[m].c)) C.dp[m]={v2,c2};
            }
        }
    }
    return C;
}
vector<int> qnodes;
void get_nodes(int node,int start,int end,int l,int r){
    if(r<start||end<l) return;
    if(l<=start&&end<=r){
        qnodes.push_back(node);
        return;
    }
    int mid=(start+end)/2;
    get_nodes(2*node,start,mid,l,r);
    get_nodes(2*node+1,mid+1,end,l,r);
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i) cin>>arr[i];
    build(1,1,n);
    while(m--){
        int l,r,k;
        cin>>l>>r>>k;
        qnodes.clear();
        get_nodes(1,1,n,l,r);
        int low=-2000000000000LL,high=2000000000000LL,ans=-INF;
        while(low<=high){
            int mid=low+(high-low)/2;
            EvalNode cur=evaluate(tree[qnodes[0]],mid);
            for(int i=1;i<(int)qnodes.size();++i) cur=merge_eval(cur,evaluate(tree[qnodes[i]],mid),mid);
            
            int mval=-INF,mc=-INF;
            for(int i=0;i<4;++i){
                if(cur.dp[i].v>mval||(cur.dp[i].v==mval&&cur.dp[i].c>mc)){
                    mval=cur.dp[i].v;mc=cur.dp[i].c;
                }
            }
            if(mc>=k){ans=mval+mid*k;low=mid+1;}
            else high=mid-1;
        }
        cout<<ans<<"\n";
    }
}