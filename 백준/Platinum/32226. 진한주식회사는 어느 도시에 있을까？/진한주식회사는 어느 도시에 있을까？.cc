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
    return acos(max(-1.0,min(1.0,(ax*bx+ay*by)/(sqrt(ax*ax+ay*ay)*sqrt(bx*bx+by*by)))));
}
double dist(pt a,pt b){
    double dx=a.x-b.x,dy=a.y-b.y;
    return sqrt(dx*dx+dy*dy);
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
    double tri=cal_s(P1,P2,P3);
    if(tri>=0){
        double area=tri+cal_a(c,angle(B,P1,P2))+cal_a(a,angle(C,P2,P3))+cal_a(b,angle(A,P3,P1));
        cout<<area;
    }
    else{
        pt cen[]={A,B,C};
        double rad[]={b,c,a};
        int pairs[][2]={{0,1},{1,2},{2,0}};
        for(auto &p:pairs){
            int i=p[0],j=p[1],k=3-i-j;
            double d=dist(cen[i],cen[j]);
            double ri=rad[i],rj=rad[j],rk=rad[k];
            if(d>ri+rj||d<fabs(ri-rj)) continue;
            double av=(ri*ri-rj*rj+d*d)/(2*d);
            double h=sqrt(max(0.0,ri*ri-av*av));
            double ex=(cen[j].x-cen[i].x)/d;
            double ey=(cen[j].y-cen[i].y)/d;
            pt q1={cen[i].x+av*ex+h*(-ey), cen[i].y+av*ey+h*ex};
            pt q2={cen[i].x+av*ex-h*(-ey), cen[i].y+av*ey-h*ex};
            if(dist(q1,cen[k])<=rk+1e-9 && dist(q2,cen[k])<=rk+1e-9){
                double area=cal_a(ri,angle(cen[i],q1,q2))+cal_a(rj,angle(cen[j],q1,q2));
                cout<<area;
                return 0;
            }
        }
        cout<<0;
    }
}