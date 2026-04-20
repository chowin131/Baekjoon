#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
struct Q{
    int l,r,k,id;
    bool operator<(const Q& o)const{
        if(l/316!=o.l/316) return l/316<o.l/316;
        return ((l/316)&1)?r<o.r:r>o.r;
    }
};
int n,m;
int A[100005],B[100005],cA[100005],cB[100005];
int tA[100005],tB[100005],ans[100005];
inline void addA(int i,int v){
    for(;i<=100000;i+=i&-i) tA[i]+=v;
}
inline void addB(int i,int v){
    for(;i<=100000;i+=i&-i) tB[i]+=v;
}
inline int qA(int i){
    int s=0;
    for(;i>0;i-=i&-i) s+=tA[i];
    return s;
}
inline int qB(int i){
    int s=0;
    for(;i>0;i-=i&-i) s+=tB[i];
    return s;
}

inline void add(int i){
    cA[A[i]]++;
    addA(A[i],1);
    cB[B[i]]++;
    addB(B[i],1);
}
inline void sub(int i){
    cA[A[i]]--;
    addA(A[i],-1);
    cB[B[i]]--;
    addB(B[i],-1);
}
main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>A[i];
    for(int i=1;i<=n;++i) cin>>B[i];
    cin>>m;
    vector<Q> q(m);
    for(int i=0;i<m;++i){
        cin>>q[i].l>>q[i].r>>q[i].k;
        q[i].id=i;
    }
    sort(q.begin(),q.end());
    int L=1,R=0;
    for(auto& c:q){
        while(L>c.l) add(--L);
        while(R<c.r) add(++R);
        while(L<c.l) sub(L++);
        while(R>c.r) sub(R--);
        int sq=sqrt(c.k);
        int res=0;
        for(int x=1;x<=sq;++x){
            if(cA[x]) res+=cA[x]*qB(c.k/x);
            if(cB[x]) res+=cB[x]*qA(c.k/x);
        }
        ans[c.id]=res-qA(sq)*qB(sq);
    }
    for(int i=0;i<m;++i) cout<<ans[i]<<"\n";
}