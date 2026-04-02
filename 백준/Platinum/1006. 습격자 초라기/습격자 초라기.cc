#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int INF=1e9;
int n,w;
int a[10005],b[10005],c[10005],A[10005],B[10005];
void solve(int type){
    for(int i=0;i<=n;i++)a[i]=b[i]=c[i]=INF;
    if(type==0){
        a[0]=0;
        a[1]=(A[1]+B[1]<=w)?1:2;
        b[1]=1;
        c[1]=1;
    }
    else if(type==1){
        if(A[1]+A[n]>w)return;
        a[0]=INF;
        a[1]=1;
        b[1]=0;
        c[1]=INF;
    }
    else if(type==2){
        if(B[1]+B[n]>w)return;
        a[0]=INF;
        a[1]=1;
        b[1]=INF;
        c[1]=0;
    }
    else if(type==3){
        if(A[1]+A[n]>w||B[1]+B[n]>w)return;
        a[0]=INF;
        a[1]=0;
        b[1]=INF;
        c[1]=INF;
    }
    int end=(type==3)?n-1:n;
    for(int i=2;i<=end;i++){
        b[i]=a[i-1]+1;
        if(A[i-1]+A[i]<=w)b[i]=min(b[i],c[i-1]+1);
        c[i]=a[i-1]+1;
        if(B[i-1]+B[i]<=w)c[i]=min(c[i],b[i-1]+1);
        a[i]=min({a[i-1]+2,b[i]+1,c[i]+1});
        if(A[i]+B[i]<=w)a[i]=min(a[i],a[i-1]+1);
        if(A[i-1]+A[i]<=w&&B[i-1]+B[i]<=w)a[i]=min(a[i],a[i-2]+2);
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n>>w;
        for(int i=1;i<=n;i++)cin>>A[i];
        for(int i=1;i<=n;i++)cin>>B[i];
        if(n==1){
            if(A[1]+B[1]<=w)cout<<1<<'\n';
            else cout<<2<<'\n';
            continue;
        }
        int ans=INF;
        solve(0);
        ans=min(ans,a[n]);
        solve(1);
        ans=min(ans,c[n]+1);
        solve(2);
        ans=min(ans,b[n]+1);
        solve(3);
        ans=min(ans,a[n-1]+2);
        cout<<ans<<'\n';
    }
}