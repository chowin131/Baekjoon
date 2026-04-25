#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
struct Ed{int u,v,t,c,id;};
vector<Ed> eds;
int n,m;
struct Tr{
    int t,c;
    vector<p> ep;
} bst;
void upd(const Tr& tr){
    if(bst.t==-1||bst.t*bst.c>tr.t*tr.c||(bst.t*bst.c==tr.t*tr.c&&tr.t<bst.t))bst=tr;
}
struct DSU{
    vector<int> p;
    DSU(int n){p.resize(n);iota(p.begin(),p.end(),0);}
    int fnd(int i){return p[i]==i?i:p[i]=fnd(p[i]);}
    bool uni(int i,int j){
        int u=fnd(i),v=fnd(j);
        if(u!=v){p[u]=v;return true;}
        return false;
    }
};
Tr mst(int wt,int wc){
    sort(eds.begin(),eds.end(),[wt,wc](const Ed& a,const Ed& b){
        int wa=a.t*wt+a.c*wc,wb=b.t*wt+b.c*wc;
        if(wa!=wb)return wa<wb;
        if(a.t!=b.t)return a.t<b.t;
        return a.id<b.id;
    });
    DSU dsu(n);
    Tr r={0,0,{}};
    for(auto& e:eds){
        if(dsu.uni(e.u,e.v)){
            r.t+=e.t;
            r.c+=e.c;
            r.ep.push_back({e.u,e.v});
        }
    }
    upd(r);
    return r;
}
void slv(const Tr& A,const Tr& B){
    int wt=A.c-B.c,wc=B.t-A.t;
    Tr C=mst(wt,wc);
    int crs=(B.t-A.t)*(C.c-A.c)-(B.c-A.c)*(C.t-A.t);
    if(crs>=0)return;
    slv(A,C);
    slv(C,B);
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    if(!(cin>>n>>m))return 0;
    for(int i=0;i<m;++i){
        int u,v,t,c;
        cin>>u>>v>>t>>c;
        eds.push_back({u,v,t,c,i});
    }
    bst.t=-1;
    Tr A=mst(1,0);
    Tr B=mst(0,1);
    slv(A,B);
    cout<<bst.t<<" "<<bst.c<<"\n";
    for(auto& e:bst.ep)
        cout<<e.f<<" "<<e.s<<"\n";
}