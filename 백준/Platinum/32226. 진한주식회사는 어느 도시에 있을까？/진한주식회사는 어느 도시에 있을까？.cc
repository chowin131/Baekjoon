#include <iostream>
#include <cmath>
using namespace std;
struct pt{double x,y;};
double cal_a(double r,double ang){
    return r*r*ang/2-r*r*sin(ang)/2;
}
double cal_s(pt a,pt b,pt c){
    return (a.x*b.y+b.x*c.y+c.x*a.y-a.y*b.x-b.y*c.x-c.y*a.x)/2;
}
double angle(pt center,pt p1,pt p2){
    double ax=p1.x-center.x, ay=p1.y-center.y;
    double bx=p2.x-center.x, by=p2.y-center.y;
    return acos((ax*bx+ay*by)/(sqrt(ax*ax+ay*ay)*sqrt(bx*bx+by*by)));
}
signed main(){
    cout<<fixed;
    cout.precision(6);
    double a,b,c;
    cin>>a>>b>>c;
    double T=sqrt((a+b+c)*(b+c-a)*(a+c-b)*(a+b-c));
    pt A={0,0},B={a,0};
    pt C={(a*a+c*c-b*b)/(2*a),T/(2*a)};
    pt P1={(a*a+b*b-c*c)/(2*a),T/(2*a)};
    pt P2={(a*a-c*c)*(a*a+b*b-c*c)/(2*a*b*b),(c*c-a*a)*T/(2*a*b*b)};
    pt P3={(c*c*(a*a+b*b)-(a*a-b*b)*(a*a-b*b))/(2*a*c*c),(b*b-a*a)*T/(2*a*c*c)};
    double area=cal_s(P1,P2,P3)+cal_a(c,angle(B,P1,P2))+cal_a(a,angle(C,P2,P3))+cal_a(b,angle(A,P3,P1));
    cout<<area;
}