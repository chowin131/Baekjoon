#include <bits/stdc++.h>
using namespace std;
#define eps 1e-9
struct pt{
    double x,y,z;
    pt operator+(pt o){return {x+o.x,y+o.y,z+o.z};}
    pt operator-(pt o){return {x-o.x,y-o.y,z-o.z};}
    pt operator*(double t){return {x*t,y*t,z*t};}
};
vector<pt> P;
int n;
double phi;

double dot(pt a,pt b){ return a.x*b.x+a.y*b.y+a.z*b.z; }
pt cross(pt a,pt b){ return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x}; }
double norm(pt a){ return sqrt(dot(a,a)); }
pt normalize(pt a){
    double l=norm(a);
    return {a.x/l,a.y/l,a.z/l};
}
int count_star(pt cen){
    int cnt=0;
    double cs=cos(phi);
    for(int i=0;i<n;i++)
        if(dot(cen,P[i])>=cs-eps) cnt++;
    return cnt;
}
double cal_angle(pt a,pt b){ return acos(max(-1.0,min(1.0,dot(a,b)))); }

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    P.resize(n);
    for(int i=0;i<n;i++){
        double x,y,z;
        cin>>x>>y>>z;
        P[i]=normalize({x,y,z});
    }
    double deg;
    cin>>deg;
    phi=deg*M_PI/180.0;
    int result=1;
    for(int i=0;i<n;i++) result=max(result,count_star(P[i]));
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(cal_angle(P[i],P[j])>2*phi+eps) continue;

            pt mid=normalize(P[i]+P[j]);
            pt nv=cross(P[i],P[j]);
            if(norm(nv)<eps) continue;

            nv=normalize(nv);
            double d=dot(mid,P[i]);
            if(abs(d)<eps) continue;

            double ct=cos(phi)/d;
            if(ct>1.0+eps||ct<-1.0-eps) continue;

            ct=max(-1.0,min(1.0,ct));
            pt C1=mid*ct+nv*sqrt(max(0.0,1.0-ct*ct));
            pt C2=mid*ct+nv*(-sqrt(max(0.0,1.0-ct*ct)));
            result=max(result,count_star(C1));
            result=max(result,count_star(C2));
        }
    }
    cout<<result;
}