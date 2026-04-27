#include <bits/stdc++.h>
using namespace std;
#define int long long
struct pt{int x,y,id;};
int ccw(pt a,pt b,pt c){
    int res=(b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
    if(res>0)return 1;
    if(res<0)return -1;
    return 0;
}
vector<pt> chull(vector<pt>& v){
    if(v.size()<=2){
        vector<pt> res=v;
        sort(res.begin(),res.end(),[](pt a,pt b){
            if(a.x!=b.x)return a.x<b.x;
            return a.y<b.y;
        });
        return res;
    }
    sort(v.begin(),v.end(),[](pt a,pt b){
        if(a.x!=b.x)return a.x<b.x;
        return a.y<b.y;
    });
    vector<pt> u,l;
    for(auto p:v){
        while(u.size()>=2&&ccw(u[u.size()-2],u.back(),p)>=0)u.pop_back();
        u.push_back(p);
        while(l.size()>=2&&ccw(l[l.size()-2],l.back(),p)<=0)l.pop_back();
        l.push_back(p);
    }
    vector<pt> res=l;
    for(int i=(int)u.size()-2;i>0;i--)res.push_back(u[i]);
    return res;
}
bool in_Tk(int k,pt p,const vector<pt>& h){
    int sz=h.size();
    pt pr=h[(k-1+sz)%sz];
    pt cr=h[k];
    pt nx=h[(k+1)%sz];
    if(ccw(pr,nx,p)>0)return false;
    if(ccw(pr,cr,p)<0)return false;
    if(ccw(cr,nx,p)<0)return false;
    return true;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,k;
    cin>>n>>k;
    vector<pt> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i].x>>v[i].y;
        v[i].id=i;
    }
    sort(v.begin(),v.end(),[](pt a,pt b){
        if(a.x!=b.x)return a.x<b.x;
        return a.y<b.y;
    });
    vector<pt> u,l;
    for(auto p:v){
        while(u.size()>=2&&ccw(u[u.size()-2],u.back(),p)>=0)u.pop_back();
        u.push_back(p);
        while(l.size()>=2&&ccw(l[l.size()-2],l.back(),p)<=0)l.pop_back();
        l.push_back(p);
    }
    vector<pt> h=l;
    for(int i=(int)u.size()-2;i>0;i--)h.push_back(u[i]);
    if(h.size()<3){
        cout<<0;
        return 0;
    }
    vector<int> h_idx(n,-1);
    for(int i=0;i<(int)h.size();i++)h_idx[h[i].id]=i;
    vector<vector<pt>> s(h.size());
    int usz=u.size();
    int lsz=l.size();
    for(auto p:v){
        if(h_idx[p.id]!=-1)continue;
        int iu=lower_bound(u.begin(),u.end(),p,[](pt a,pt b){return a.x<b.x;})-u.begin();
        vector<int> cand;
        for(int j=iu-3;j<=iu+3;j++){
            if(j>=0&&j<usz){
                int idx=h_idx[u[j].id];
                if(idx!=-1)cand.push_back(idx);
            }
        }
        int il=lower_bound(l.begin(),l.end(),p,[](pt a,pt b){return a.x<b.x;})-l.begin();
        for(int j=il-3;j<=il+3;j++){
            if(j>=0&&j<lsz){
                int idx=h_idx[l[j].id];
                if(idx!=-1)cand.push_back(idx);
            }
        }
        sort(cand.begin(),cand.end());
        cand.erase(unique(cand.begin(),cand.end()),cand.end());
        for(int c:cand){
            if(in_Tk(c,p,h))s[c].push_back(p);
        }
    }
    int ans=0;
    int hs=h.size();
    if(hs==k)ans+=n-hs;
    for(int i=0;i<hs;i++){
        vector<pt> sub=s[i];
        sub.push_back(h[(i-1+hs)%hs]);
        sub.push_back(h[(i+1)%hs]);
        vector<pt> sh=chull(sub);
        if(hs-3+(int)sh.size()==k)ans++;
    }
    cout<<ans;
}