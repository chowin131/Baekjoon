#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
struct pt3{ll x,y,z;};
struct pt3d{
    ld x,y,z;
    pt3d operator-(const pt3d& o)const{return {x-o.x,y-o.y,z-o.z};}
    pt3d cross(const pt3d& o)const{return {y*o.z-z*o.y,z*o.x-x*o.z,x*o.y-y*o.x};}
    ld dot(const pt3d& o)const{return x*o.x+y*o.y+z*o.z;}
};
struct pt2ll{__int128_t x,y;};
int n,q;
pt3 P[1010];
pt3d Pp[1010];
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    if(!(cin>>n>>q)) return 0;
    for(int i=0;i<n;i++) cin>>P[i].x>>P[i].y>>P[i].z;
    set<pair<int,int>> edges;
    if(n<4){
        for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) edges.insert({i,j});
    }else{
        mt19937 rng(42);
        vector<int> perm(n);
        iota(perm.begin(),perm.end(),0);
        shuffle(perm.begin(),perm.end(),rng);
        pt3 tmpP[1010];
        for(int i=0;i<n;i++) tmpP[i]=P[i];
        for(int i=0;i<n;i++) P[i]=tmpP[perm[i]];
        for(int i=0;i<n;i++){
            Pp[i].x=P[i].x+1e-9L*cosl(P[i].x*1.2+P[i].y*2.3+i);
            Pp[i].y=P[i].y+1e-9L*sinl(P[i].y*1.3+P[i].z*2.4+i);
            Pp[i].z=P[i].z+1e-9L*cosl(P[i].z*1.4+P[i].x*2.5+i);
        }
        vector<array<int,3>> faces;
        pt3d n012=(Pp[1]-Pp[0]).cross(Pp[2]-Pp[0]);
        if(n012.dot(Pp[3]-Pp[0])<0){
            faces.push_back({0,1,2});faces.push_back({0,2,3});
            faces.push_back({0,3,1});faces.push_back({1,3,2});
        }else{
            faces.push_back({0,2,1});faces.push_back({0,1,3});
            faces.push_back({0,3,2});faces.push_back({1,2,3});
        }
        for(int i=4;i<n;i++){
            vector<array<int,3>> nxt;
            set<pair<int,int>> bnd;
            for(auto f:faces){
                pt3d nm=(Pp[f[1]]-Pp[f[0]]).cross(Pp[f[2]]-Pp[f[0]]);
                if(nm.dot(Pp[i]-Pp[f[0]])>0){
                    auto ae=[&](int u,int v){
                        if(bnd.count({v,u})) bnd.erase({v,u});
                        else bnd.insert({u,v});
                    };
                    ae(f[0],f[1]);ae(f[1],f[2]);ae(f[2],f[0]);
                }else nxt.push_back(f);
            }
            for(auto e:bnd) nxt.push_back({e.first,e.second,i});
            faces=nxt;
        }
        for(auto f:faces){
            for(int j=0;j<3;j++){
                int u=f[j],v=f[(j+1)%3];
                if(u>v) swap(u,v);
                edges.insert({u,v});
            }
        }
    }
    while(q--){
        ll a,b,c,d;
        cin>>a>>b>>c>>d;
        int drop=0;
        if(abs(a)>=abs(b)&&abs(a)>=abs(c)) drop=0;
        else if(abs(b)>=abs(a)&&abs(b)>=abs(c)) drop=1;
        else drop=2;
        vector<pt2ll> pl;
        auto eval=[&](pt3 p)->ll{return a*p.x+b*p.y+c*p.z+d;};
        auto add_pt=[&](ld px,ld py,ld pz){
            ld X=0,Y=0;
            if(drop==0){X=py;Y=pz;}
            else if(drop==1){X=px;Y=pz;}
            else{X=px;Y=py;}
            pl.push_back({(__int128_t)round(X*1e10),(__int128_t)round(Y*1e10)});
        };
        for(auto eg:edges){
            int i=eg.first,j=eg.second;
            ll v1=eval(P[i]),v2=eval(P[j]);
            if(v1==0&&v2==0){
                add_pt(P[i].x,P[i].y,P[i].z);add_pt(P[j].x,P[j].y,P[j].z);
            }else if(v1==0) add_pt(P[i].x,P[i].y,P[i].z);
            else if(v2==0) add_pt(P[j].x,P[j].y,P[j].z);
            else if((v1>0&&v2<0)||(v1<0&&v2>0)){
                ld t=(ld)v1/(ld)(v1-v2);
                add_pt(P[i].x+t*(P[j].x-P[i].x),P[i].y+t*(P[j].y-P[i].y),P[i].z+t*(P[j].z-P[i].z));
            }
        }
        sort(pl.begin(),pl.end(),[](const pt2ll& A,const pt2ll& B){
            if(A.x!=B.x) return A.x<B.x;
            return A.y<B.y;
        });
        pl.erase(unique(pl.begin(),pl.end(),[](const pt2ll& A,const pt2ll& B){
            return A.x==B.x&&A.y==B.y;
        }),pl.end());
        if(pl.size()<3){cout<<fixed<<setprecision(3)<<0.0<<"\n";continue;}
        auto ccw=[](pt2ll A,pt2ll B,pt2ll C){
            return (B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x);
        };
        vector<pt2ll> U,L;
        for(auto p:pl){
            while(U.size()>=2&&ccw(U[U.size()-2],U.back(),p)>=0) U.pop_back();
            U.push_back(p);
            while(L.size()>=2&&ccw(L[L.size()-2],L.back(),p)<=0) L.pop_back();
            L.push_back(p);
        }
        vector<pt2ll> ch=L;
        for(int i=(int)U.size()-2;i>=1;i--) ch.push_back(U[i]);
        __int128_t area=0;
        for(int i=0;i<(int)ch.size();i++){
            pt2ll p1=ch[i],p2=ch[(i+1)%ch.size()];
            area+=p1.x*p2.y-p2.x*p1.y;
        }
        if(area<0) area=-area;
        ld f_area=(ld)area/2.0/1e20;
        ld len=sqrtl((ld)a*a+(ld)b*b+(ld)c*c);
        ld mult=1.0;
        if(drop==0) mult=len/abs((ld)a);
        else if(drop==1) mult=len/abs((ld)b);
        else mult=len/abs((ld)c);
        cout<<fixed<<setprecision(3)<<(double)(f_area*mult)<<"\n";
    }
    return 0;
}