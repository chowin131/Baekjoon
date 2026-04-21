#include <bits/stdc++.h>
using namespace std;
#define int long long
using p=pair<int,int>;
#define f first
#define s second
struct pt{int x,y,rk;};
bool cmp(pt a,pt b){return a.y*b.x<b.y*a.x;}
int ccw(pt a,pt b,pt c){
    int r=(b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
    if(r>0)return 1;
    if(r<0)return -1;
    return 0;
}
struct nd{
    vector<pt> l,u;
}tr[400005];
void bld(int n,int s,int e,const vector<pt>& a){
    vector<pt> lp;
    for(auto& p:a){
        if(lp.empty()||lp.back().x!=p.x)lp.push_back(p);
    }
    vector<pt> l;
    for(auto& p:lp){
        while(l.size()>=2&&ccw(l[l.size()-2],l.back(),p)<=0)l.pop_back();
        l.push_back(p);
    }
    tr[n].l=l;
    vector<pt> up;
    for(auto& p:a){
        if(up.empty()||up.back().x!=p.x)up.push_back(p);
        else up.back()=p;
    }
    vector<pt> u;
    for(auto& p:up){
        while(u.size()>=2&&ccw(u[u.size()-2],u.back(),p)>=0)u.pop_back();
        u.push_back(p);
    }
    tr[n].u=u;
    if(s==e)return;
    int m=(s+e)/2;
    vector<pt> la,ra;
    for(auto& p:a){
        if(p.rk<=m)la.push_back(p);
        else ra.push_back(p);
    }
    bld(2*n,s,m,la);bld(2*n+1,m+1,e,ra);
}
int sh(const vector<pt>& h,int c,int d){
    if(h.empty())return 2e18;
    int lo=0,hi=(int)h.size()-1,b=hi;
    while(lo<=hi){
        int m=lo+(hi-lo)/2;
        if(m==(int)h.size()-1){
            b=m;
            break;
        }
        int dx=h[m+1].x-h[m].x,dy=h[m+1].y-h[m].y;
        if(c*dx+d*dy>=0){
            b=m;
            hi=m-1;
        }
        else lo=m+1;
    }
    return c*h[b].x+d*h[b].y;
}
bool chk(int n,pt a,pt b){
    int c=b.y-a.y,d=a.x-b.x,lm=a.x*b.y-a.y*b.x,mn;
    if(d>0)mn=sh(tr[n].l,c,d);
    else if(d<0)mn=sh(tr[n].u,c,d);
    else mn=sh(tr[n].l,c,d);
    return mn<lm;
}
bool qry(int n,int s,int e,int l,int r,pt a,pt b){
    if(s>r||e<l)return 0;
    if(l<=s&&e<=r)return chk(n,a,b);
    int m=(s+e)/2;
    return qry(2*n,s,m,l,r,a,b)||qry(2*n+1,m+1,e,l,r,a,b);
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int k,m;
    if(!(cin>>k>>m))return 0;
    vector<pt> a(k);
    for(int i=0;i<k;++i){
        cin>>a[i].x>>a[i].y;
        a[i].rk=0;
    }
    sort(a.begin(),a.end(),cmp);
    vector<pt> u;
    for(int i=0;i<k;++i){
        if(u.empty())u.push_back(a[i]);
        else{
            if(a[i].y*u.back().x==u.back().y*a[i].x){
                if(a[i].x<u.back().x)u.back()=a[i];
            }
            else u.push_back(a[i]);
        }
    }
    int n=u.size();
    for(int i=0;i<n;++i)u[i].rk=i;
    vector<pt> sx=u;
    sort(sx.begin(),sx.end(),[](pt u,pt v){
        if(u.x!=v.x)return u.x<v.x;
        return u.y<v.y;
    });
    if(n>0)bld(1,0,n-1,sx);
    while(m--){
        int x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
        pt A={x1,y1,0},B={x2,y2,0},O={0,0,0};
        if(ccw(O,A,B)<0)swap(A,B);
        if(n==0){
            cout<<"N\n";
            continue;
        }
        int qL=upper_bound(u.begin(),u.end(),A,cmp)-u.begin();
        int qR=lower_bound(u.begin(),u.end(),B,cmp)-u.begin()-1;
        if(qL<=qR&&qry(1,0,n-1,qL,qR,A,B))cout<<"Y\n";
        else cout<<"N\n";
    }
    return 0;
}