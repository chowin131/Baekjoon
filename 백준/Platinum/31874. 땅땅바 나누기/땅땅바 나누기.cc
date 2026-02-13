#include <bits/stdc++.h>
using namespace std;
using p=pair<int,int>;
#define f first
#define s second
#define int long long
const int INF=INT64_MAX;

main(){
    ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
    int n;
    cin>>n;
    vector<pair<double,int>> v(n);
    vector<double> incl(n);
    unordered_map<double,pair<int,int>> m;
    int POS=0,NEG=0;
    int tot=0,cnt=0;
    for(int i=0;i<n;i++){
        int x,y,val;
        cin>>x>>y>>val;
        if(x==0&&y==0) continue;
        tot+=val;

        if(x<0||(x==0&&y<0)) x*=-1,y*=-1,val*=-1;
        if(val>0) POS+=val;
        else NEG+=-val;
        if(x==0) v[cnt]={INF,val},incl[cnt]=INF;
        else v[cnt]={(double)y/(double)x,val},incl[cnt]=(double)y/(double)x;

        m[incl[cnt]]={x,y};
        cnt++;
    }
    v.resize(cnt);
    incl.resize(cnt);
    n=cnt;
    if(n==0){
        cout<<"1 0";
        return 0;
    }
    sort(incl.begin(),incl.end());
    incl.erase(unique(incl.begin(),incl.end()),incl.end());
    int Size=incl.size();
    vector<int> c(Size);
    for(int i=0;i<n;i++){
        double a=v[i].f;
        int b=v[i].s;
        int idx=lower_bound(incl.begin(),incl.end(),a)-incl.begin();
        c[idx]+=b;
    }
    int best=-INF,cur=0,idx=-1;
    if(best<min(POS,NEG)){
        best=min(POS,NEG);
        idx=-1;
    }
    for(int i=0;i<Size;i++){
        cur+=c[i];
        int mn=min(POS-cur,NEG+cur);
        if(best<mn){
            best=mn;
            idx=i;
        }
    }
    if(idx==-1){
        p t=m[incl[0]];
        if(t.f==0) cout<<"0 1";
        else cout<<t.s-t.f<<" "<<t.f;
        return 0;
    }
    if(idx==Size-1){
        p t=m[incl[Size-1]];
        if(t.f==0) cout<<"1 0";
        else cout<<t.s+t.f<<" "<<t.f;
        return 0;
    }
    p a=m[incl[idx]],b=m[incl[idx+1]];
    cout<<a.s+b.s<<" "<<a.f+b.f;
}