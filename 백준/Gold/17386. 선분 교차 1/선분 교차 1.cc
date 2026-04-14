#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
struct pt{
    int x,y;
};
int ccw(pt a,pt b,pt c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
bool onSeg(pt a,pt b,pt p){
    return min(a.x,b.x)<=p.x&&p.x<=max(a.x,b.x)&&min(a.y,b.y)<=p.y&&p.y<=max(a.y,b.y);
}
int sign(int x){
    return (x>0)-(x<0);
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    pt a1,a2,b1,b2;
    cin>>a1.x>>a1.y>>a2.x>>a2.y;
    cin>>b1.x>>b1.y>>b2.x>>b2.y;
    int d1=ccw(a1,a2,b1),d2=ccw(a1,a2,b2);
    int d3=ccw(b1,b2,a1),d4=ccw(b1,b2,a2);
    if (sign(d1)*sign(d2)<0&&sign(d3)*sign(d4)<0){
        double t=(double)d3/(d3-d4);
        cout<<1;
        //cout<<"\n"<<fixed<<setprecision(10)<<a1.x+t*(a2.x-a1.x)<<" "<<a1.y+t*(a2.y-a1.y);
        return 0;
    }
    vector<pt> P;
    if (d1==0&&onSeg(a1,a2,b1)) P.push_back(b1);
    if (d2==0&&onSeg(a1,a2,b2)) P.push_back(b2);
    if (d3==0&&onSeg(b1,b2,a1)) P.push_back(a1);
    if (d4==0&&onSeg(b1,b2,a2)) P.push_back(a2);
    if (P.empty()){
        cout<<0;
        return 0;
    }
    bool flag=1;
    for (auto&p:P)
        if (p.x!=P[0].x||p.y!=P[0].y){
            flag=0;
            break;
        }
    cout<<1;
    //if (flag) cout<<"\n"<<P[0].x<<" "<<P[0].y;
}