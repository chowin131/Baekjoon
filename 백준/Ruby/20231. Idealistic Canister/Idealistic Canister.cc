#include <bits/stdc++.h>
using namespace std;

struct pt{double x,y;};
pt operator-(pt a,pt b){return{a.x-b.x,a.y-b.y};}
pt operator+(pt a,pt b){return{a.x+b.x,a.y+b.y};}
pt operator*(pt a,double d){return{a.x*d,a.y*d};}
double crs(pt a,pt b){return a.x*b.y-a.y*b.x;}
double dot(pt a,pt b){return a.x*b.x+a.y*b.y;}
double len(pt a){return hypot(a.x,a.y);}

bool in_P(pt o,const vector<pt>&p){
    int n=p.size();
    for(int i=0;i<n;++i)if(crs(p[(i+1)%n]-p[i],o-p[i])<=0)return 0;
    return 1;
}

double d_OP(pt o,const vector<pt>&p){
    int n=p.size();
    double md=1e9;
    if(in_P(o,p)){
        for(int i=0;i<n;++i){
            pt a=p[i],b=p[(i+1)%n];
            md=min(md,abs(crs(b-a,o-a))/len(b-a));
        }
        return -md;
    }else{
        for(int i=0;i<n;++i){
            pt a=p[i],b=p[(i+1)%n];
            if(dot(b-a,o-a)>=0&&dot(a-b,o-b)>=0)md=min(md,abs(crs(b-a,o-a))/len(b-a));
            else md=min({md,len(o-a),len(o-b)});
        }
        return md;
    }
}

double f_sq(pt o,const vector<pt>&p){
    double mx=0;
    for(auto&v:p){
        double dx=o.x-v.x,dy=o.y-v.y;
        if(dx*dx+dy*dy>mx)mx=dx*dx+dy*dy;
    }
    return mx;
}

pt g_MEC(const vector<pt>&p){
    double lx=-2000,rx=2000;
    for(int i=0;i<70;++i){
        double m1=lx+(rx-lx)/3,m2=rx-(rx-lx)/3;
        auto ev=[&](double x){
            double ly=-2000,ry=2000;
            for(int j=0;j<70;++j){
                double my1=ly+(ry-ly)/3,my2=ry-(ry-ly)/3;
                if(f_sq({x,my1},p)<f_sq({x,my2},p))ry=my2;else ly=my1;
            }
            return f_sq({x,ly},p);
        };
        if(ev(m1)<ev(m2))rx=m2;else lx=m1;
    }
    double x=lx,ly=-2000,ry=2000;
    for(int j=0;j<70;++j){
        double my1=ly+(ry-ly)/3,my2=ry-(ry-ly)/3;
        if(f_sq({x,my1},p)<f_sq({x,my2},p))ry=my2;else ly=my1;
    }
    return {x,ly};
}
double g_R(const vector<pt>&p,double d,pt mec,double rm){
    if(d_OP(mec,p)>=d-1e-9)return rm;
    double ans_sq=1e18;
    int n=p.size();
    if(d>=0){
        for(int i=0;i<n;++i){
            pt a=p[i],b=p[(i+1)%n],c=p[(i+2)%n];
            pt ab=b-a;double lab=len(ab);
            pt n1={ab.y/lab,-ab.x/lab};
            pt a1=a+n1*d,b1=b+n1*d;
            double l=0,r=1;
            for(int k=0;k<60;++k){
                double m1=l+(r-l)/3,m2=r-(r-l)/3;
                if(f_sq(a1+(b1-a1)*m1,p)<f_sq(a1+(b1-a1)*m2,p))r=m2;else l=m1;
            }
            ans_sq=min(ans_sq,f_sq(a1+(b1-a1)*l,p));
            pt bc=c-b;double lbc=len(bc);
            pt n2={bc.y/lbc,-bc.x/lbc};
            double t1=atan2(n1.y,n1.x),t2=atan2(n2.y,n2.x);
            if(t2<t1)t2+=2*M_PI;
            l=t1;r=t2;
            for(int k=0;k<60;++k){
                double m1=l+(r-l)/3,m2=r-(r-l)/3;
                if(f_sq(b+pt{cos(m1),sin(m1)}*d,p)<f_sq(b+pt{cos(m2),sin(m2)}*d,p))r=m2;else l=m1;
            }
            ans_sq=min(ans_sq,f_sq(b+pt{cos(l),sin(l)}*d,p));
        }
    }else{
        for(int i=0;i<n;++i){
            pt a=p[i],b=p[(i+1)%n];
            pt ab=b-a;double lab=len(ab);
            pt n1={ab.y/lab,-ab.x/lab};
            double c1=dot(a,n1);
            pt p0=n1*(c1+d),v={-n1.y,n1.x};
            double tmin=-1e5,tmax=1e5;bool ok=1;
            for(int j=0;j<n;++j){
                if(i==j)continue;
                pt aj=p[j],bj=p[(j+1)%n];
                pt abj=bj-aj;double labj=len(abj);
                pt nj={abj.y/labj,-abj.x/labj};
                double cj=dot(aj,nj);
                double den=dot(v,nj),num=cj+d-dot(p0,nj);
                if(abs(den)<1e-9){if(num<-1e-9){ok=0;break;}}
                else if(den>0)tmax=min(tmax,num/den);
                else tmin=max(tmin,num/den);
            }
            if(ok&&tmin<=tmax){
                double l=tmin,r=tmax;
                for(int k=0;k<60;++k){
                    double m1=l+(r-l)/3,m2=r-(r-l)/3;
                    if(f_sq(p0+v*m1,p)<f_sq(p0+v*m2,p))r=m2;else l=m1;
                }
                ans_sq=min(ans_sq,f_sq(p0+v*l,p));
            }
        }
    }
    return sqrt(ans_sq);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    while(cin>>n&&n){
        vector<pt>P(n);
        for(int i=0;i<n;++i)cin>>P[i].x>>P[i].y;
        int m;cin>>m;
        vector<pt>Q(m);
        for(int i=0;i<m;++i)cin>>Q[i].x>>Q[i].y;
        pt mecp=g_MEC(P),mecq=g_MEC(Q);
        double rmp=sqrt(f_sq(mecp,P)),rmq=sqrt(f_sq(mecq,Q));
        
        double ld=-2000,rd=2000;
        for(int iter=0;iter<70;++iter){
            double m1=ld+(rd-ld)/3,m2=rd-(rd-ld)/3;
            if(max(g_R(P,m1,mecp,rmp),g_R(Q,-m1,mecq,rmq))<max(g_R(P,m2,mecp,rmp),g_R(Q,-m2,mecq,rmq)))rd=m2;else ld=m1;
        }
        cout<<fixed<<setprecision(9)<<max(g_R(P,ld,mecp,rmp),g_R(Q,-ld,mecq,rmq))*2<<'\n';
    }
}