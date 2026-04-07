#include <bits/stdc++.h>
#define int long long
using namespace std;
struct pt{int x,y,z;};
vector<pt> a;
int best,cnt;

void upd(int i,int j){
    int d=(a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y)+(a[i].z-a[j].z)*(a[i].z-a[j].z);
    if(d<best) best=d,cnt=1;
    else if(d==best) cnt++;
}

void solve(int l,int r){
    if(r-l<=3){
        for(int i=l;i<r;i++) for(int j=i+1;j<r;j++) upd(i,j);
        return;
    }
    int m=(l+r)/2;
    int mx=a[m].x;
    solve(l,m);
    solve(m,r);
    vector<int> v;
    for(int i=l;i<r;i++){
        int dx=a[i].x-mx;
        if(dx*dx<=best) v.push_back(i);
    }
    sort(v.begin(),v.end(),[](int i,int j){return a[i].y<a[j].y;});
    for(int i=0;i<(int)v.size();i++){
        for(int j=i+1;j<(int)v.size();j++){
            int dy=a[v[j]].y-a[v[i]].y;
            if(dy*dy>best) break;
            if((v[i]<m)!=(v[j]<m)) upd(v[i],v[j]);
        }
    }
}

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    a.resize(n);
    for(int i=0;i<n;i++) cin>>a[i].x>>a[i].y>>a[i].z;
    sort(a.begin(),a.end(),[](pt&p,pt&q){
        if(p.x!=q.x) return p.x<q.x;
        if(p.y!=q.y) return p.y<q.y;
        return p.z<q.z;
    });
    a.erase(unique(a.begin(),a.end(),[](pt&p,pt&q){
        return p.x==q.x&&p.y==q.y&&p.z==q.z;
    }),a.end());
    n=a.size();
    best=INT64_MAX; cnt=0;
    solve(0,n);
    cout<<best<<"\n"<<cnt;
}