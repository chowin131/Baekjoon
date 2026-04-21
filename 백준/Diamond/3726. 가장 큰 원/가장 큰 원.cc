#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<double,double>;
#define f first
#define s second
bool check(double R,int N,double L,const vector<array<double,4>>& segs){
    vector<p> ivs;
    for(int i=0;i<N;++i){
        double x1=segs[i][0],y1=segs[i][1];
        double x2=segs[i][2],y2=segs[i][3];
        vector<double> cands;
        if(R*R>=y1*y1){
            double d=sqrt(max((double)0.0,R*R-y1*y1));
            cands.push_back(x1+d);
            cands.push_back(x1-d);
        }
        if(R*R>=y2*y2){
            double d=sqrt(max((double)0.0,R*R-y2*y2));
            cands.push_back(x2+d);
            cands.push_back(x2-d);
        }
        double dx=x2-x1,dy=y2-y1,L2=dx*dx+dy*dy;
        if(L2>0&&dy!=0){
            double Rs=R*sqrt(L2),c=dx*y1-dy*x1;
            double x3=(Rs-c)/dy,D3=(x3-x1)*dx-y1*dy;
            if(D3>=-1e-9&&D3<=L2+1e-9)cands.push_back(x3);
            double x4=(-Rs-c)/dy,D4=(x4-x1)*dx-y1*dy;
            if(D4>=-1e-9&&D4<=L2+1e-9)cands.push_back(x4);
        }
        if(!cands.empty()){
            double mn=cands[0],mx=cands[0];
            for(double x:cands){
                if(x<mn)mn=x;
                if(x>mx)mx=x;
            }
            ivs.push_back({mn,mx});
        }
    }
    sort(ivs.begin(),ivs.end());
    double curr=0;
    for(auto& iv:ivs){
        if(iv.f>curr+1e-9)if(curr<=L+1e-9)return true;
        if(iv.s>curr)curr=iv.s;
    }
    if(curr<L-1e-9)return true;
    if(L==0&&curr<1e-9)return true;
    return false;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int t;
    if(!(cin>>t))return 0;
    while(t--){
        int n;
        double L;
        cin>>n>>L;
        vector<array<double,4>> segs(n);
        for(int i=0;i<n;++i)cin>>segs[i][0]>>segs[i][1]>>segs[i][2]>>segs[i][3];
        double low=0,high=40000.0;
        for(int i=0;i<80;++i){
            double mid=low+(high-low)/2.0;
            if(check(mid,n,L,segs))low=mid;
            else high=mid;
        }
        cout<<fixed<<setprecision(3)<<low<<'\n';
    }
    return 0;
}