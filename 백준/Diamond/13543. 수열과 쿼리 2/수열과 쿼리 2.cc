#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

uint32_t C[12][12];

struct Node{
    int l,r,sz;
    uint32_t val,pri;
    uint32_t S[11];
}t[300005];

int root=0,cnt=0;
mt19937 rng(1337);

void pull(int x){
    t[x].sz=t[t[x].l].sz+t[t[x].r].sz+1;
    uint32_t szL=t[t[x].l].sz;
    for(int k=0;k<=10;++k) t[x].S[k]=0;
    if(t[x].l) for(int k=0;k<=10;++k) t[x].S[k]=t[t[x].l].S[k];
    uint32_t p_szL[11];
    p_szL[0]=1;
    for(int k=1;k<=10;++k) p_szL[k]=p_szL[k-1]*szL;
    for(int k=0;k<=10;++k) t[x].S[k]+=p_szL[k]*t[x].val;
    if(t[x].r){
        uint32_t off=szL+1;
        uint32_t p_off[11];
        p_off[0]=1;
        for(int k=1;k<=10;++k) p_off[k]=p_off[k-1]*off;
        for(int k=0;k<=10;++k){
            uint32_t sum=0;
            for(int c=0;c<=k;++c) sum+=C[k][c]*p_off[k-c]*t[t[x].r].S[c];
            t[x].S[k]+=sum;
        }
    }
}

void split(int x,int k,int &l,int &r){
    if(!x){ l=r=0; return; }
    int szL=t[t[x].l].sz;
    if(k<=szL){
        r=x;
        split(t[x].l,k,l,t[x].l);
        pull(r);
    }else{
        l=x;
        split(t[x].r,k-szL-1,t[x].r,r);
        pull(l);
    }
}

void merge(int &x,int l,int r){
    if(!l||!r){ x=l?l:r; return; }
    if(t[l].pri>t[r].pri){
        x=l;
        merge(t[x].r,t[l].r,r);
    }else{
        x=r;
        merge(t[x].l,l,t[r].l);
    }
    pull(x);
}

int newNode(uint32_t v){
    int x=++cnt;
    t[x].sz=1; t[x].val=v; t[x].pri=rng();
    t[x].l=t[x].r=0;
    pull(x);
    return x;
}

main(){
    cin.tie(0)->sync_with_stdio(0);
    for(int i=0;i<=11;++i){
        C[i][0]=1;
        for(int j=1;j<=i;++j) C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    int n; cin>>n;
    for(int i=0;i<n;++i){
        uint32_t v; cin>>v;
        int x=newNode(v);
        merge(root,root,x);
    }
    int m; cin>>m;
    auto q_ins=[&](int p,uint32_t v){
        int L,R;
        split(root,p,L,R);
        int nn=newNode(v);
        merge(L,L,nn);
        merge(root,L,R);
    };
    auto q_del=[&](int p){
        int L,M,R;
        split(root,p+1,L,R);
        split(L,p,L,M);
        merge(root,L,R);
    };
    auto q_upd=[&](int p,uint32_t v){
        int L,M,R;
        split(root,p+1,L,R);
        split(L,p,L,M);
        t[M].val=v;
        pull(M);
        merge(L,L,M);
        merge(root,L,R);
    };
    auto q_qry=[&](int l,int r,int k){
        int L,M,R;
        split(root,r+1,L,R);
        split(L,l,L,M);
        uint32_t ans=0;
        for(int c=0;c<=k;++c) ans+=C[k][c]*t[M].S[c];
        cout<<ans<<"\n";
        merge(L,L,M);
        merge(root,L,R);
    };
    while(m--){
        int op; cin>>op;
        if(op==1){
            int p;
            uint32_t v;
            cin>>p>>v;
            q_ins(p,v);
        }else if(op==2){
            int p; cin>>p;
            q_del(p);
        }else if(op==3){
            int p; uint32_t v; cin>>p>>v;
            q_upd(p,v);
        }else if(op==4){
            int l,r,k; cin>>l>>r>>k;
            q_qry(l,r,k);
        }
    }
}