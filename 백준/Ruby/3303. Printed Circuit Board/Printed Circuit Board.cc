#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
const double EPS=1e-9;
int sgn(double x){
    if(x<-EPS)return -1;
    if(x>EPS)return 1;
    return 0;
}
struct Pt{double x,y;};
Pt operator+(Pt a,Pt b){return {a.x+b.x,a.y+b.y};}
Pt operator-(Pt a,Pt b){return {a.x-b.x,a.y-b.y};}
Pt operator*(Pt a,double b){return {a.x*b,a.y*b};}
Pt operator/(Pt a,double b){return {a.x/b,a.y/b};}
double crs(Pt a,Pt b){return a.x*b.y-a.y*b.x;}
double crs2(Pt s,Pt a,Pt b){return crs(a-s,b-s);}
double ccw(vector<Pt>& pts,int a,int b,int c){return crs2(pts[a],pts[b],pts[c]);}
bool insec(Pt a,Pt b,Pt c,Pt d,Pt& res){
    double oa=crs2(c,d,a),ob=crs2(c,d,b);
    double oc=crs2(a,b,c),od=crs2(a,b,d);
    if(sgn(oa)*sgn(ob)<0&&sgn(oc)*sgn(od)<0){
        res=(a*ob-b*oa)/(ob-oa);
        return true;
    }
    return false;
}
int st_type=0,hf_apex=0;
bool hf_gap=0,hb_pos=0;
void prune(vector<int>& stk,vector<Pt>& pts,int c,int nxt){
    while(stk.size()){
        int lst=stk.back();
        if(ccw(pts,0,lst,nxt)<=0.0&&ccw(pts,c,nxt,lst)>0.0)stk.pop_back();
        else break;
    }
}
void proc_vis(vector<Pt>& pts,vector<int>& stk,int prv,int c,int nxt){
    if(ccw(pts,0,stk.back(),nxt)>0.0){
        if(ccw(pts,0,prv,c)<0.0&&ccw(pts,prv,c,nxt)>0.0){
            st_type=2;hb_pos=true;
        }
        else{
            stk.push_back(nxt);
            st_type=0;
        }
    }
    else{
        if(ccw(pts,0,prv,c)>0.0&&ccw(pts,prv,c,nxt)<0.0){
            st_type=2;hb_pos=false;
        }
        else{
            stk.pop_back();
            prune(stk,pts,c,nxt);
            if(ccw(pts,c,nxt,stk.back())<0.0){
                st_type=1;hf_apex=nxt;hf_gap=false;
            }
            else{
                stk.push_back(nxt);
                st_type=0;
            }
        }
    }
}
void proc_hf(vector<Pt>& pts,vector<int>& stk,int prv,int c,int nxt){
    Pt tmp;
    hf_gap=hf_gap||insec(pts[stk.back()],pts[hf_apex],pts[c],pts[nxt],tmp);
    if(ccw(pts,stk.back(),hf_apex,nxt)<0.0||(hf_apex==c&&ccw(pts,prv,c,nxt)>0.0))hf_gap=false;
    if(ccw(pts,0,stk.back(),nxt)>0.0&&hf_gap){
        stk.push_back(nxt);
        st_type=0;
    }
}
void proc_hb(vector<Pt>& pts,vector<int>& stk,int c,int nxt){
    bool crsd=(ccw(pts,0,stk.back(),nxt)>0.0)^hb_pos;
    if(!crsd)return;
    if(hb_pos){
        stk.pop_back();
        prune(stk,pts,c,nxt);
        if(ccw(pts,c,nxt,stk.back())<0.0){
            st_type=1;hf_apex=nxt;hf_gap=false;
        }
        else{
            stk.push_back(nxt);
            st_type=0;
        }
    }
    else{
        stk.push_back(nxt);
        st_type=0;
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<Pt> pts(n+1);
    pts[0]={0.0,0.0};
    for(int i=1;i<=n;++i)cin>>pts[i].x>>pts[i].y;
    int fst=1;
    for(int i=2;i<=n;++i){
        double d=crs2(pts[0],pts[fst],pts[i]);
        if(d<0.0||(d==0.0&&pts[i].x<pts[fst].x))fst=i;
    }
    int pf=(fst==1?n:fst-1);
    int nf=(fst==n?1:fst+1);
    double dir=(crs2(pts[nf],pts[fst],pts[pf])>0.0)?1.0:-1.0;
    auto adv=[&](int idx,double d){
        int step=(d>0.0)?1:n-1;
        return (idx-1+step)%n+1;
    };
    vector<int> stk;
    int c=adv(fst,dir);
    stk.push_back(fst);
    stk.push_back(c);
    st_type=0;
    for(int i=2;i<n;++i){
        int prv=adv(c,-dir);
        int nxt=adv(c,dir);
        if(st_type==0)proc_vis(pts,stk,prv,c,nxt);
        else if(st_type==1)proc_hf(pts,stk,prv,c,nxt);
        else proc_hb(pts,stk,c,nxt);
        c=nxt;
    }
    vector<bool> ret(n+1,false);
    for(int idx:stk) ret[idx]=true;
    int cnt=0;
    for(int i=1;i<=n;++i)
        if(ret[i])cnt++;
    cout<<cnt<<"\n";
    bool f_prt=false;
    for(int i=1;i<=n;++i){
        if(ret[i]){
            if(f_prt)cout<<" ";
            cout<<i;
            f_prt=1;
        }
    }
}