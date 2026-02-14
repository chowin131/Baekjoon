#include <bits/stdc++.h>
using namespace std;
const double eps=1e-12;
main(){
    ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
    int w,h;
    cin>>w>>h;
    int n,d;
    cin>>n>>d;
    vector<int> a(n+1),p(n+1);
    a[0]=0;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>p[i];
    auto solve=[&](vector<pair<int,int>>& seg, double tx)->double{
        if(seg.empty()) return 0;
        if(tx<eps){
            double c=0;
            for(auto [dy,pi]:seg) c+=dy*pi;
            return c;
        }
        int pmin=INT_MAX;
        for(auto [dy,pi]:seg) pmin=min(pmin,pi);
        double lo=0,hi=pmin-eps;
        for(int it=0;it<200;it++){
            double mid=(lo+hi)/2,sx=0;
            for(auto [dy,pi]:seg){
                double temp=mid/pi;
                sx+=dy*temp/sqrt(1.0-temp*temp);
            }
            if(sx<tx) lo=mid;
            else hi=mid;
        }
        double C=(lo+hi)/2,cost=0;
        for(auto [dy,pi]:seg){
            double cs=sqrt(1.0-(C/pi)*(C/pi));
            cost+=pi*dy/cs;
        }
        return cost;
    };
    double ans=1e18;
    int idx=1;
    for(int i=1;i<=n;i++) if(d>a[i]) idx=i+1;
    {
        vector<pair<int,int>> all;
        for(int i=1;i<idx;i++) all.push_back({a[i]-a[i-1],p[i]});
        all.push_back({d-a[idx-1],p[idx]});
        ans=min(ans,solve(all,w));
    }
    for(int k=idx;k<=n;k++){
        vector<pair<int,int>> all;
        for(int i=1;i<=k;i++) all.push_back({a[i]-a[i-1],p[i]});
        for(int i=idx;i<=k;i++){
            int lo=max(a[i-1],d),hi=a[i];
            if(hi>lo) all.push_back({hi-lo,p[i]});
        }
        ans=min(ans,solve(all,w));
    }
    cout<<fixed<<setprecision(6)<<ans;
}