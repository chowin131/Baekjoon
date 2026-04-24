#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

struct pt{double x,y;};
pt operator-(pt a,pt b){return {a.x-b.x,a.y-b.y};}
pt operator+(pt a,pt b){return {a.x+b.x,a.y+b.y};}
pt operator*(double s,pt a){return {s*a.x,s*a.y};}
double cross(pt a,pt b){return a.x*b.y-a.y*b.x;}
double cross(pt o,pt a,pt b){return cross(a-o,b-o);}
double dot(pt a,pt b){return a.x*b.x+a.y*b.y;}
int n,m,G;
pt S;
vector<vector<pt>> poly;
bool inside(pt Q,const vector<pt>& P){
    int k=P.size();
    for(int j=0;j<k;++j){
        pt A=P[j],B=P[(j+1)%k];
        if(abs(cross(A,B,Q))<=1e-9){
            if(Q.x>=min(A.x,B.x)-1e-9&&Q.x<=max(A.x,B.x)+1e-9&&Q.y>=min(A.y,B.y)-1e-9&&Q.y<=max(A.y,B.y)+1e-9)return 0;
        }
    }
    int cnt=0;
    for(int j=0;j<k;++j){
        pt A=P[j],B=P[(j+1)%k];
        if(A.y>B.y)swap(A,B);
        if(Q.y>=A.y&&Q.y<B.y){
            double x_int=A.x+(Q.y-A.y)*(B.x-A.x)/(B.y-A.y);
            if(x_int>Q.x)cnt++;
        }
    }
    return cnt%2==1;
}

pt get_E(pt v){
    double tx=1e18,ty=1e18;
    if(v.x>1e-9)tx=(n-S.x)/v.x;
    else if(v.x<-1e-9)tx=(0-S.x)/v.x;
    if(v.y>1e-9)ty=(m-S.y)/v.y;
    else if(v.y<-1e-9)ty=(0-S.y)/v.y;
    double t=min(tx,ty);
    return S+t*v;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>S.x>>S.y>>G;
    poly.resize(G);
    vector<pt> cands={{0,0},{(double)n,0},{(double)n,(double)m},{0,(double)m}};
    for(int i=0;i<G;++i){
        int k;cin>>k;
        poly[i].resize(k);
        for(int j=0;j<k;++j){
            cin>>poly[i][j].x>>poly[i][j].y;
            cands.push_back(poly[i][j]);
        }
    }
    double mx=-1;
    pt best={-1,-1};
    for(pt cand:cands){
        pt v=cand-S;
        if(abs(v.x)<=1e-9&&abs(v.y)<=1e-9)continue;
        pt E=get_E(v);
        bool valid=1;
        for(int i=0;i<G;++i){
            vector<double> us={0.0,1.0};
            int k=poly[i].size();
            for(int j=0;j<k;++j){
                pt A=poly[i][j],B=poly[i][(j+1)%k];
                double d=cross(E-S,B-A);
                if(abs(d)>1e-9){
                    double u=cross(A-S,B-A)/d;
                    double vv=cross(A-S,E-S)/d;
                    if(vv>=-1e-9&&vv<=1+1e-9)us.push_back(u);
                }
                else{
                    if(abs(cross(A-S,E-S))<=1e-9){
                        double L2=dot(E-S,E-S);
                        if(L2>1e-9){
                            us.push_back(dot(A-S,E-S)/L2);
                            us.push_back(dot(B-S,E-S)/L2);
                        }
                    }
                }
            }
            sort(us.begin(),us.end());
            vector<double> cln;
            for(double u:us){
                if(u>=-1e-9&&u<=1+1e-9){
                    if(cln.empty()||u-cln.back()>1e-9)cln.push_back(max((double)0,min((double)1,u)));
                }
            }
            for(int j=0;j+1<cln.size();++j){
                if(cln[j+1]-cln[j]>1e-7){
                    double umid=(cln[j]+cln[j+1])/2.0;
                    pt Q=S+umid*(E-S);
                    if(inside(Q,poly[i])){
                        valid=0;break;
                    }
                }
            }
            if(!valid)break;
        }
        if(valid){
            double d=sqrt(dot(E-S,E-S));
            if(d>mx+1e-7){
                mx=d;best=E;
            }
            else if(abs(d-mx)<=1e-7){
                if(E.x<best.x-1e-7)best=E;
                else if(abs(E.x-best.x)<=1e-7&&E.y<best.y-1e-7)best=E;
            }
        }
    }
    if(mx<0)cout<<"GG";
    else{
        cout<<fixed;
        cout.precision(3);
        cout<<best.x<<" "<<best.y;
    }
}