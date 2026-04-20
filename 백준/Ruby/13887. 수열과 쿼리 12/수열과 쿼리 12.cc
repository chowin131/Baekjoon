#include <bits/stdc++.h>
using namespace std;
using p = pair<int,int>;
#define int long long
#define f first
#define s second

const int MOD=1e9+7;
const int MAXV=200005;

int oA[MAXV];
vector<int> vs;
int rv[MAXV*2];

int ch[MAXV][2],pa[MAXV],sz[MAXV],act[MAXV];
int rt,ncnt;

void pull(int x){sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+act[x];}
void rot(int x){
    int y=pa[x],z=pa[y],k=(ch[y][1]==x);
    ch[z][ch[z][1]==y]=x;pa[x]=z;
    ch[y][k]=ch[x][k^1];if(ch[x][k^1])pa[ch[x][k^1]]=y;
    ch[x][k^1]=y;pa[y]=x;
    pull(y);pull(x);
}
void splay(int x,int g=0){
    while(pa[x]!=g){
        int y=pa[x],z=pa[y];
        if(z!=g){
            if((ch[y][1]==x)^(ch[z][1]==y))rot(x);
            else rot(y);
        }
        rot(x);
    }
    if(!g)rt=x;
}
int fkth(int k){
    int u=rt;
    while(u){
        int lsz=sz[ch[u][0]];
        if(k<=lsz)u=ch[u][0];
        else if(act[u]&&k==lsz+1){splay(u);return u;}
        else{k-=lsz+act[u];u=ch[u][1];}
    }
    return 0;
}
int bld(int l,int r,int p){
    if(l>r)return 0;
    int m=l+(r-l)/2;
    pa[m]=p;act[m]=1;
    ch[m][0]=bld(l,m-1,m);
    ch[m][1]=bld(m+1,r,m);
    pull(m);return m;
}

struct Upd{int p,ov,nv;};
vector<Upd> upds;
struct Qry{int l,r,t,id,type;};
vector<Qry> qrys;
int csv[MAXV];

int sl[MAXV],scnt;
void inord(int u){
    if(!u)return;
    inord(ch[u][0]);
    sl[u]=++scnt;
    inord(ch[u][1]);
}

int val[MAXV];
int frq[MAXV*2];
int dcnt,S1,S2,S3;

inline void add(int x){
    if(!x)return;
    if(++frq[x]==1){
        dcnt++;
        int v=rv[x];
        int v2=1LL*v*v%MOD;
        int v3=1LL*v2*v%MOD;
        S1+=v;if(S1>=MOD)S1-=MOD;
        S2+=v2;if(S2>=MOD)S2-=MOD;
        S3+=v3;if(S3>=MOD)S3-=MOD;
    }
}
inline void del(int x){
    if(!x)return;
    if(--frq[x]==0){
        dcnt--;
        int v=rv[x];
        int v2=1LL*v*v%MOD;
        int v3=1LL*v2*v%MOD;
        S1-=v;if(S1<0)S1+=MOD;
        S2-=v2;if(S2<0)S2+=MOD;
        S3-=v3;if(S3<0)S3+=MOD;
    }
}

const int B=4000;
bool cmp(const Qry& a,const Qry& b){
    int bl=a.l/B,br=a.r/B;
    int obl=b.l/B,obr=b.r/B;
    if(bl!=obl)return bl<obl;
    if(br!=obr)return bl%2==0?br<obr:br>obr;
    return br%2==0?a.t<b.t:a.t>b.t;
}

int pwr(int b,int e){
    int r=1;b%=MOD;
    while(e>0){
        if(e%2)r=1LL*r*b%MOD;
        b=1LL*b*b%MOD;e/=2;
    }
    return r;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i){
        cin>>oA[i];
        vs.push_back(oA[i]);
    }
    int m;cin>>m;
    struct RQ{int t,a,b;};
    vector<RQ> rq(m);
    for(int i=0;i<m;++i){
        cin>>rq[i].t>>rq[i].a;
        if(rq[i].t!=3){
            cin>>rq[i].b;
            if(rq[i].t==2||rq[i].t==4)vs.push_back(rq[i].b);
        }
    }
    sort(vs.begin(),vs.end());
    vs.erase(unique(vs.begin(),vs.end()),vs.end());
    auto gc=[&](int x){return lower_bound(vs.begin(),vs.end(),x)-vs.begin()+1;};
    for(int i=0;i<vs.size();++i)rv[i+1]=vs[i]%MOD;

    rt=bld(1,n,0);ncnt=n;
    for(int i=1;i<=n;++i)csv[i]=gc(oA[i]);

    int tmr=0,qidx=0;
    for(int i=0;i<m;++i){
        int t=rq[i].t;
        if(t==1||t==5){
            int u=fkth(rq[i].a),v=fkth(rq[i].b);
            qrys.push_back({u,v,tmr,qidx++,t});
        }else if(t==2){
            int u=fkth(rq[i].a),cy=gc(rq[i].b);
            upds.push_back({u,csv[u],cy});
            csv[u]=cy;tmr++;
        }else if(t==3){
            int u=fkth(rq[i].a);
            act[u]=0;pull(u);
            upds.push_back({u,csv[u],0});
            csv[u]=0;tmr++;
        }else if(t==4){
            int z=rq[i].a,cy=gc(rq[i].b);
            ncnt++;act[ncnt]=1;sz[ncnt]=1;
            if(z==0){
                if(!rt)rt=ncnt;
                else{
                    int u=rt;while(ch[u][0])u=ch[u][0];
                    splay(u);ch[u][0]=ncnt;pa[ncnt]=u;
                    pull(ncnt);pull(u);
                }
            }else{
                int u=fkth(z),r=ch[u][1];
                ch[u][1]=ncnt;pa[ncnt]=u;
                ch[ncnt][1]=r;if(r)pa[r]=ncnt;
                pull(ncnt);pull(u);
            }
            upds.push_back({ncnt,0,cy});
            csv[ncnt]=cy;tmr++;
        }
    }
    inord(rt);
    for(auto& q:qrys){q.l=sl[q.l];q.r=sl[q.r];}
    for(auto& u:upds)u.p=sl[u.p];
    for(int i=1;i<=n;++i)val[sl[i]]=gc(oA[i]);
    sort(qrys.begin(),qrys.end(),cmp);

    int L=1,R=0,T=0;
    vector<int> ans(qidx);
    int inv6=pwr(6,MOD-2);

    auto apply=[&](int tidx,int dir){
        int p=upds[tidx].p,ov=upds[tidx].ov,nv=upds[tidx].nv;
        if(dir==1){
            if(L<=p&&p<=R){del(ov);add(nv);}
            val[p]=nv;
        }else{
            if(L<=p&&p<=R){del(nv);add(ov);}
            val[p]=ov;
        }
    };

    for(auto& q:qrys){
        while(T<q.t)apply(T++,1);
        while(T>q.t)apply(--T,-1);
        while(R<q.r)add(val[++R]);
        while(L>q.l)add(val[--L]);
        while(R>q.r)del(val[R--]);
        while(L<q.l)del(val[L++]);

        if(q.type==1){
            int s1=S1,s2=S2,s3=S3;
            int p1=s1*s1%MOD*s1%MOD;
            int p2=3LL*s1%MOD*s2%MOD;
            int p3=2LL*s3%MOD;
            int res=(p1-p2+p3)%MOD;
            if(res<0)res+=MOD;
            ans[q.id]=res*inv6%MOD;
        }else ans[q.id]=dcnt;
    }
    for(int i=0;i<qidx;++i)cout<<ans[i]<<'\n';
    return 0;
}