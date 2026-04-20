#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

struct Q{
    int l,r,id;
    bool operator<(const Q& o)const{
        if(l/350!=o.l/350) return l/350<o.l/350;
        return r<o.r;
    }
};

int n,k,m;
int a[100005],ans[100005],fst[100005],lst[100005],fn[100005];

main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i) cin>>a[i];
    cin>>m;
    vector<Q> q(m);
    for(int i=0;i<m;++i){
        cin>>q[i].l>>q[i].r;
        q[i].id=i;
    }
    sort(q.begin(),q.end());
    int lb=-1,R=1,md=0;
    vector<int> ra;
    for(auto& c:q){
        int b=c.l/350;
        int st=(b+1)*350;
        if(c.r<st){
            int tmp=0;
            for(int i=c.l;i<=c.r;++i){
                if(!fn[a[i]]) fn[a[i]]=i;
                tmp=max(tmp,i-fn[a[i]]);
            }
            ans[c.id]=tmp;
            for(int i=c.l;i<=c.r;++i) fn[a[i]]=0;
            continue;
        }
        if(b!=lb){
            for(int x:ra) fst[x]=lst[x]=0;
            ra.clear();
            md=0;
            R=st;
            lb=b;
        }
        while(R<=c.r){
            int v=a[R];
            if(!fst[v]){
                fst[v]=R;
                ra.push_back(v);
            }
            lst[v]=R;
            md=max(md,R-fst[v]);
            R++;
        }
        int tmp=md;
        vector<int> rb;
        for(int i=st-1;i>=c.l;--i){
            int v=a[i];
            if(!lst[v]){
                lst[v]=i;
                rb.push_back(v);
            }
            tmp=max(tmp,lst[v]-i);
        }
        ans[c.id]=tmp;
        for(int v:rb) lst[v]=0;
    }
    for(int i=0;i<m;++i) cout<<ans[i]<<"\n";
}