#include<bits/stdc++.h>
using namespace std;
#define int long long
struct pt{ int x,y; };
int n,m,k;
vector<pt>P,Q;
vector<int> IN,L,U,sz;

int ccw(pt a,pt b,pt c){
    int t=(b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
    if(t>0) return 1;
    if(t<0) return -1;
    return 0;
}

inline int len(int a,int b){
    return (b-a+n)%n+1;
}

inline bool intri(pt a,pt b,pt c,pt p){
    return ccw(a,b,p)>=0&&ccw(b,c,p)>=0&&ccw(c,a,p)>=0;
}

bool in_ch(pt p){
    if(ccw(P[0],P[1],p)<0) return 0;
    if(ccw(P[0],P[n-1],p)>0) return 0;
    int l=1,r=n-1;
    while(l+1<r){
        int m=(l+r)>>1;
        if(ccw(P[0],P[m],p)>=0) l=m;
        else r=m;
    }
    return ccw(P[l],P[r],p)>0;
}

int findr(pt p){
    int l=0,r=n-1,m,b,a;
    while(l<r){
        m=(l+r+1)/2;
        b=(m-1+n)%n;
        a=(m+1)%n;
        if(ccw(p,P[0],P[n-1])<=0){
            if(ccw(p,P[m],P[b])<=0&&ccw(p,P[m],P[a])>=0&&ccw(p,P[0],P[m])<0) r=m-1;
            else l=m;
        }
        else{
            if(ccw(p,P[m],P[b])<=0||(ccw(p,P[m],P[b])>0&&ccw(p,P[m],P[a])<0&&ccw(p,P[0],P[m])>0)) r=m-1;
            else l=m;
        }
    }
    return l;
}

int findl(pt p){
    int l=0,r=n-1,m,b,a;
    while(l<r){
        m=(l+r+1)/2;
        b=(m-1+n)%n;
        a=(m+1)%n;
        if(ccw(p,P[0],P[n-1])>0){
            if(ccw(p,P[m],P[b])>0&&ccw(p,P[m],P[a])<0&&ccw(p,P[0],P[m])>0) r=m-1;
            else l=m;
        }
        else{
            if(ccw(p,P[m],P[b])>0||(ccw(p,P[m],P[b])<=0&&ccw(p,P[m],P[a])>=0&&ccw(p,P[0],P[m])<0)) r=m-1;
            else l=m;
        }
    }
    return l;
}

main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    P.resize(n);Q.resize(m);
    IN.resize(m);
    L.resize(m),U.resize(m);
    sz.resize(m);

    for(int i=0;i<n;i++) cin>>P[i].x>>P[i].y;
    for(int i=0;i<m;i++) cin>>Q[i].x>>Q[i].y;

    for(int i=0;i<m;i++){
        if(in_ch(Q[i])){ IN[i]=1; sz[i]=n; continue; }
        int left=findl(Q[i]);
        int right=findr(Q[i]);

        L[i]=(ccw(Q[i],P[left],P[(left-1+n)%n])==0)?(left-1+n)%n:left;
        U[i]=(ccw(Q[i],P[right],P[(right+1)%n])==0)?(right+1)%n:right;
        sz[i]=len(U[i],L[i])+1;
    }

    while(k--){
        int a,b;
        cin>>a>>b;
        a--,b--;

        if(IN[a]&&IN[b]){ cout<<n<<"\n"; continue; }
        if(IN[a]){ cout<<sz[b]<<"\n"; continue; }
        if(IN[b]){ cout<<sz[a]<<"\n"; continue; }

        if(intri(P[L[b]],Q[b],P[U[b]],Q[a])){ cout<<sz[b]<<"\n"; continue; }
        if(intri(P[L[a]],Q[a],P[U[a]],Q[b])){ cout<<sz[a]<<"\n"; continue; }

        if(ccw(Q[a],P[U[a]],Q[b])<=0&&ccw(P[L[b]],Q[b],Q[a])<=0){ cout<<len(U[b],L[a])+2<<"\n"; continue; }
        if(ccw(Q[b],P[U[b]],Q[a])<=0&&ccw(P[L[a]],Q[a],Q[b])<=0){ cout<<len(U[a],L[b])+2<<"\n"; continue; }
        
        cout<<len(U[a],L[b])+len(U[b],L[a])+2<<"\n";
    }
}