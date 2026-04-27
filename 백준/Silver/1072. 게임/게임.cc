#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int x,y;
    cin>>x>>y;
    int z=y*100/x;
    if(z>=99){
        cout<<-1;
        return 0;
    }
    int l=0,r=2000000000,ans=-1;
    while(l<=r){
        int m=(l+r)/2;
        int nz=(y+m)*100/(x+m);
        if(nz>z){
            ans=m;
            r=m-1;
        }
        else l=m+1;
    }
    cout<<ans;
}