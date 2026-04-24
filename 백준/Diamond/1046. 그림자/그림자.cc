#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
struct seg{
    int t;
    double p,mn,mx;
};
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<string> g(n);
    double lx=0,ly=0;
    int wall_cnt=0;
    for(int i=0;i<n;++i){
        cin>>g[i];
        for(int j=0;j<m;++j){
            if(g[i][j]=='*'){
                lx=j+0.5;
                ly=i+0.5;
            }
            else if(g[i][j]=='#'){
                wall_cnt++;
            }
        }
    }
    vector<seg> v;
    v.push_back({0,0,0,(double)m});
    v.push_back({0,(double)n,0,(double)m});
    v.push_back({1,0,0,(double)n});
    v.push_back({1,(double)m,0,(double)n});
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(g[i][j]=='#'){
                if(i-1>=0&&g[i-1][j]!='#')v.push_back({0,(double)i,(double)j,(double)j+1});
                if(i+1<n&&g[i+1][j]!='#')v.push_back({0,(double)i+1,(double)j,(double)j+1});
                if(j-1>=0&&g[i][j-1]!='#')v.push_back({1,(double)j,(double)i,(double)i+1});
                if(j+1<m&&g[i][j+1]!='#')v.push_back({1,(double)j+1,(double)i,(double)i+1});
            }
        }
    }
    vector<pair<double,double>> pts;
    for(auto& s:v){
        if(s.t==0){
            pts.push_back({s.mn,s.p});
            pts.push_back({s.mx,s.p});
        }else{
            pts.push_back({s.p,s.mn});
            pts.push_back({s.p,s.mx});
        }
    }
    vector<double> ang;
    for(auto& pt:pts)ang.push_back(atan2(pt.s-ly,pt.f-lx));
    sort(ang.begin(),ang.end());
    vector<double> ua;
    if(!ang.empty()){
        ua.push_back(ang[0]);
        for(int i=1;i<ang.size();++i){
            if(ang[i]-ua.back()>1e-11)ua.push_back(ang[i]);
        }
    }
    ua.push_back(ua[0]+2*acos(-1.0L));
    auto ft=[&](const seg& s,double dx,double dy)->double{
        double t=-1;
        if(s.t==0){
            if(abs(dy)>1e-12){
                t=(s.p-ly)/dy;
                if(t>0){
                    double px=lx+t*dx;
                    if(px>=s.mn-1e-9&&px<=s.mx+1e-9)return t;
                }
            }
        }else{
            if(abs(dx)>1e-12){
                t=(s.p-lx)/dx;
                if(t>0){
                    double py=ly+t*dy;
                    if(py>=s.mn-1e-9&&py<=s.mx+1e-9)return t;
                }
            }
        }
        return 1e18;
    };
    auto il=[&](const seg& s,double dx,double dy)->double{
        if(s.t==0)return (s.p-ly)/dy;
        return (s.p-lx)/dx;
    };
    
    double ans=0;
    for(int i=0;i<ua.size()-1;++i){
        double t1=ua[i],t2=ua[i+1];
        double mid=(t1+t2)/2.0;
        double dx=cos(mid),dy=sin(mid);
        int b=-1;
        double mt=1e18;
        for(int j=0;j<v.size();++j){
            double t=ft(v[j],dx,dy);
            if(t>0&&t<mt){
                mt=t;
                b=j;
            }
        }
        if(b!=-1){
            double d1=il(v[b],cos(t1),sin(t1));
            double d2=il(v[b],cos(t2),sin(t2));
            double p1x=lx+d1*cos(t1),p1y=ly+d1*sin(t1);
            double p2x=lx+d2*cos(t2),p2y=ly+d2*sin(t2);
            ans+=0.5*abs((p1x-lx)*(p2y-ly)-(p1y-ly)*(p2x-lx));
        }
    }
    cout<<fixed<<setprecision(16)<<max((double)0.0,(double)(n*m)-ans-wall_cnt);//벽의 개수를 빼줘야 했네...
}