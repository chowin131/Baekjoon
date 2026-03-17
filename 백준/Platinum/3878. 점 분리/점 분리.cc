#include <bits/stdc++.h>
using namespace std;
#define pt pair<int,int>
#define x first
#define y second
#define I(v) for(pt&i:v)cin>>i.x>>i.y
int t,n,m;
vector<pt> W,B;
int ccw(pt a,pt b,pt c){
    long long t=(long long)(b.x-a.x)*(c.y-a.y)-(long long)(b.y-a.y)*(c.x-a.x);
    if(t>0)return 1;
    if(t<0)return -1;
    return 0;
}
bool in_line(pt a,pt b,pt p){
    return ccw(a,b,p)==0
        &&min(a.x,b.x)<=p.x&&p.x<=max(a.x,b.x)
        &&min(a.y,b.y)<=p.y&&p.y<=max(a.y,b.y);
}
bool inter(pt a,pt b,pt c,pt d){
    int ab1=ccw(a,b,c),ab2=ccw(a,b,d),cd1=ccw(c,d,a),cd2=ccw(c,d,b);
    if(ab1==0&&ab2==0){
        if(max(min(a.x,b.x),min(c.x,d.x))>min(max(a.x,b.x),max(c.x,d.x)))return 0;
        if(max(min(a.y,b.y),min(c.y,d.y))>min(max(a.y,b.y),max(c.y,d.y)))return 0;
        return 1;
    }
    return ab1*ab2<=0&&cd1*cd2<=0;
}
vector<pt> get_ch(vector<pt> P){
    int N=P.size();
    sort(P.begin(),P.end());
    if(N<=1)return P;
    vector<pt> ch;
    for(pt p:P){
        while(ch.size()>1&&ccw(ch[ch.size()-2],ch.back(),p)<=0)ch.pop_back();
        ch.push_back(p);
    }
    int s=ch.size();
    for(int i=N-2;i>=0;i--){
        while(ch.size()>s&&ccw(ch[ch.size()-2],ch.back(),P[i])<=0)ch.pop_back();
        ch.push_back(P[i]);
    }
    if(ch.size()>1)ch.pop_back();
    return ch;
}
bool in_ch(vector<pt>&P,pt p){
    int S=P.size();
    if(ccw(P[0],P[1],p)<0)return 0;
    if(ccw(P[0],P[S-1],p)>0)return 0;
    int l=1,r=S-1;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(ccw(P[0],P[mid],p)>=0)l=mid;
        else r=mid;
    }
    return ccw(P[l],P[r],p)>=0;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    for(cin>>t;t--;){
        cin>>n>>m;
        W.assign(n,{0,0}),B.assign(m,{0,0});
        I(W);I(B);
        vector<pt> cw=get_ch(W),cb=get_ch(B);
        int sw=cw.size(),sb=cb.size();
        bool flag=0;
        if(sw<3||sb<3){
            if(sw==1&&sb==1) flag=(cw[0]==cb[0]);
            else if(sw==1&&sb==2) flag=in_line(cb[0],cb[1],cw[0]);
            else if(sw==2&&sb==1) flag=in_line(cw[0],cw[1],cb[0]);
            else if(sw==2&&sb==2) flag=inter(cw[0],cw[1],cb[0],cb[1]);
            else if(sw==1) flag=in_ch(cb,cw[0]);
            else if(sb==1) flag=in_ch(cw,cb[0]);
            else if(sw==2){
                for(int i=0;i<sb&&!flag;i++) flag=inter(cw[0],cw[1],cb[i],cb[(i+1)%sb]);
                if(!flag) flag=in_ch(cb,cw[0])||in_ch(cb,cw[1]);
            }
            else{
                for(int i=0;i<sw&&!flag;i++) flag=inter(cb[0],cb[1],cw[i],cw[(i+1)%sw]);
                if(!flag) flag=in_ch(cw,cb[0])||in_ch(cw,cb[1]);
            }
        }
        else{
            for(pt i:cw){if(in_ch(cb,i)){flag=1;break;}}
            for(pt i:cb){if(in_ch(cw,i)){flag=1;break;}}
            for(int i=0;i<sw&&!flag;i++){
                pt a=cw[i],b=cw[(i+1)%sw];
                for(int j=0;j<sb&&!flag;j++){
                    pt c=cb[j],d=cb[(j+1)%sb];
                    if(inter(a,b,c,d))flag=1;
                }
            }
        }
        cout<<(flag?"NO":"YES")<<"\n";
    }
}