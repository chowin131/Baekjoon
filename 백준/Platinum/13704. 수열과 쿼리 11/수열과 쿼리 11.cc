#include <bits/stdc++.h>
using namespace std;
#define int long long
using p=pair<int,int>;
#define f first
#define s second
const int B=320;
struct Qry{int l,r,id;};
bool cmp(const Qry& a,const Qry& b){
    int bl=a.l/B,br=b.l/B;
    if(bl!=br)return bl<br;
    return bl%2==0?a.r<b.r:a.r>b.r;
}
int n,k,m;
int P[100005];
int cnt[2100000];
int cur;
int res[100005];
inline void add(int x){
    cur+=cnt[P[x]^k];
    cnt[P[x]]++;
}
inline void del(int x){
    cnt[P[x]]--;
    cur-=cnt[P[x]^k];
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        int x;cin>>x;
        P[i]=P[i-1]^x;
    }
    cin>>m;
    vector<Qry> q(m);
    for(int i=0;i<m;++i){
        cin>>q[i].l>>q[i].r;
        q[i].l--;
        q[i].id=i;
    }
    sort(q.begin(),q.end(),cmp);
    int L=0,R=-1;
    for(int i=0;i<m;++i){
        while(L>q[i].l)add(--L);
        while(R<q[i].r)add(++R);
        while(L<q[i].l)del(L++);
        while(R>q[i].r)del(R--);
        res[q[i].id]=cur;
    }
    for(int i=0;i<m;++i)cout<<res[i]<<'\n';
    return 0;
}