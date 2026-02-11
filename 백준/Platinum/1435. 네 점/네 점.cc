#include <iostream>
#include <cmath>
using namespace std;
struct pt{ double x,y,z,r; };
struct P2{ double x,y; };
const double EPS=1e-8;
bool oncircle(const pt& c,double x,double y){
    double dx=x-c.x,dy=y-c.y;
    double v=dx*dx+dy*dy-c.r*c.r;
    return fabs(v)<=1e-8L*(1.0L+c.r*c.r);
}
int circle_inter(const pt& a,const pt& b,P2 p[2]){
    double dx=b.x-a.x,dy=b.y-a.y;
    double d=hypotl(dx,dy);
    if(d<EPS) return 0;
    if(d>a.r+b.r+EPS) return 0;
    if(d<fabs(a.r-b.r)-EPS) return 0;
    double x=(a.r*a.r-b.r*b.r+d*d)/(2*d);
    double h2=a.r*a.r-x*x;
    if(h2<0&&h2>-EPS) h2=0;
    if(h2<0) return 0;
    double h=sqrtl(h2);
    double ux=dx/d,uy=dy/d;
    double px=a.x+x*ux,py=a.y+x*uy;
    double rx=-uy*h,ry=ux*h;

    p[0]={px+rx,py+ry};
    if(h<=EPS) return 1;
    p[1]={px-rx,py-ry};
    return 2;
}

bool check(double a,double x2,double y2,double r0,double r1,double r2){
    double x3=(r0*r0-r1*r1+a*a)/(2*a);
    if(fabs(y2)<=EPS){
        double s=r0*r0-x3*x3;
        if(s<-1e-9L) return 0;
        if(s<0) s=0;
        double need2=(x3-x2)*(x3-x2)+s;
        if(fabs(need2-r2*r2)>1e-8L*(1.0L+r2*r2)) return 0;
        double need1=(x3-a)*(x3-a)+s;
        if(fabs(need1-r1*r1)>1e-8L*(1.0L+r1*r1)) return 0;
        return 1;
    }
    else{
        double y3=(r0*r0-r2*r2-2*x3*x2+x2*x2+y2*y2)/(2*y2);
        double z2=r0*r0-x3*x3-y3*y3;
        if(z2<-1e-9L) return 0;
        if(z2<0) z2=0;

        double need2=(x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)+z2;
        if(fabs(need2-r2*r2)>1e-8L*(1.0L+r2*r2)) return 0;

        double need1=(x3-a)*(x3-a)+y3*y3+z2;
        if(fabs(need1-r1*r1)>1e-8L*(1.0L+r1*r1)) return 0;

        return 1;
    }
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    double arr[4][4];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) cin>>arr[i][j];
    double a=arr[0][1],b=arr[0][2],c=arr[1][2];
    if(a+b<c||a+c<b||b+c<a){
        cout<<"NO";
        return 0;
    }
    double T=sqrt((a+b+c)*(b+c-a)*(a+c-b)*(a+b-c));
    double x=(a*a+b*b-c*c)/(2*a);
    double y=T/(2*a);
    if(check(a,x,y,arr[0][3],arr[1][3],arr[2][3])) cout<<"YES";
    else cout<<"NO";
}