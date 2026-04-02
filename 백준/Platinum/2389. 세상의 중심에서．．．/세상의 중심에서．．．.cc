#include <bits/stdc++.h>
using namespace std;
#define eps 1e-9
struct pt{
    double x,y;
};
struct cir{
    pt ct;
    double r;
};
double dist(pt a,pt b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
cir make_cir(const vector<pt>&points){
    if(points.size()==0) return {{0,0},0};
    else if(points.size()==1) return {points[0],0};
    else if(points.size()==2) return {{(points[0].x+points[1].x)/2.0,(points[0].y+points[1].y)/2.0},sqrt(dist(points[0],points[1]))/2.0};
    else{
        pt p1=points[0],p2=points[1],p3=points[2];
        double D=2.0*((p1.x*(p2.y-p3.y))+(p2.x*(p3.y-p1.y))+(p3.x*(p1.y-p2.y)));
        if(abs(D)<eps){
            double d12=dist(p1,p2),d13=dist(p1,p3),d23=dist(p2,p3);
            if(d12>=d13&&d12>=d23) return {(p1.x+p2.x)/2.0,(p1.y+p2.y)/2.0,sqrt(dist(p1,p2))/2.0};
            if(d13>=d12&&d13>=d23) return {(p1.x+p3.x)/2.0,(p1.y+p3.y)/2.0,sqrt(dist(p1,p3))/2.0};
            return {(p2.x+p3.x)/2.0,(p2.y+p3.y)/2.0,sqrt(dist(p2,p3))/2.0};
        }
        double p1_sq=p1.x*p1.x+p1.y*p1.y;
        double p2_sq=p2.x*p2.x+p2.y*p2.y;
        double p3_sq=p3.x*p3.x+p3.y*p3.y;
        
        double centerX=(p1_sq*(p2.y-p3.y)+p2_sq*(p3.y-p1.y)+p3_sq*(p1.y-p2.y))/D;
        double centerY=(p1_sq*(p3.x-p2.x)+p2_sq*(p1.x-p3.x)+p3_sq*(p2.x-p1.x))/D;
        
        return{{centerX,centerY},sqrt(dist(p1,{centerX,centerY}))};
    }
}
cir welzl(vector<pt>&P,vector<pt> R,int remain){
    if(remain==0||R.size()==3) return make_cir(R);
    pt p=P[remain-1];
    cir mec=welzl(P,R,remain-1);
    if(dist(p,mec.ct)<mec.r*mec.r+eps) return mec;
    R.push_back(p);
    return welzl(P,R,remain-1);
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    int n;
    cin>>n;
    vector<pt> points(n);
    for(int i=0;i<n;i++)
        cin>>points[i].x>>points[i].y;
    
    unsigned seed=chrono::system_clock::now().time_since_epoch().count();
    shuffle(points.begin(),points.end(),default_random_engine(seed));
    
    cir result=welzl(points,{},n);
    cout<<result.ct.x<<" "<<result.ct.y<<' ';
    cout<<fixed;
    cout.precision(10);
    cout<<result.r;
}