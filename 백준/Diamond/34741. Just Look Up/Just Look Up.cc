#include <bits/stdc++.h>
using namespace std;
#define eps 1e-9
struct pt{
    double x,y,z;
    pt operator+(pt o){return {x+o.x,y+o.y,z+o.z};}
    pt operator-(pt o){return {x-o.x,y-o.y,z-o.z};}
    pt operator*(double t){return {x*t,y*t,z*t};}
};
double dot(pt a,pt b){return a.x*b.x+a.y*b.y+a.z*b.z;}
double norm(pt a){return sqrt(dot(a,a));}
pt normalize(pt a){double l=norm(a);return {a.x/l,a.y/l,a.z/l};}

int n;
vector<pt> P;

pair<double,int> nearInfo(pt d){
    double mx=-1e18;int idx=0;
    for(int i=0;i<n;i++){double v=dot(d,P[i]);if(v>mx)mx=v,idx=i;}
    return {mx,idx};
}

pt moveAway(pt d,int i){
    double di=dot(d,P[i]);
    pt proj={P[i].x-di*d.x,P[i].y-di*d.y,P[i].z-di*d.z};
    double l=norm(proj);
    if(l<1e-12) return d;
    return normalize(d-proj*(1.0/l));
}

mt19937 rng(42);
pt randDir(){
    uniform_real_distribution<double> dist(-1,1);
    pt p;
    do{p={dist(rng),dist(rng),dist(rng)};}while(norm(p)<eps);
    return normalize(p);
}

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    P.resize(n);
    for(int i=0;i<n;i++){
        double x,y,z;cin>>x>>y>>z;
        P[i]=normalize({x,y,z});
    }
    double bestDot=1.0;
    vector<pt> starts;
    for(int i=0;i<n;i++) starts.push_back(normalize(P[i]*(-1.0)));
    for(int i=0;i<5000;i++) starts.push_back(randDir());

    for(auto s:starts){
        auto [cur,ci]=nearInfo(s);
        for(double step=0.5;step>1e-6;step*=0.95){
            pt nd=moveAway(s,ci);
            nd=normalize(s+(nd-s)*step);
            auto [nv,ni]=nearInfo(nd);
            if(nv<cur) s=nd,cur=nv,ci=ni;
            else step*=0.5;
        }
        bestDot=min(bestDot,cur);
    }
    double ang=acos(max(-1.0,min(1.0,bestDot)));
    if(ang>M_PI/2.0-eps) ang=M_PI/2.0;
    cout<<fixed<<setprecision(5)<<ang*180.0/M_PI<<"\n";
}