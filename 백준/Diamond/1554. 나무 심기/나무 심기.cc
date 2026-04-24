#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
int c[1005][1005];
main(){
    cin.tie(0)->sync_with_stdio(0);
    int t,w,h,d;
    cin>>t>>w>>h>>d;
    if(t==1){
        cout<<(w+1)*(h+1)%1000000000;
        return 0;
    }
    for(int i=0;i<=1000;i++){
        c[i][0]=1;
        for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j-1]+c[i-1][j])%1000000000;
    }
    int ans=0;
    for(int x=0;x<=w;x++){
        for(int y=0;y<=h;y++){
            if(!x&&!y)continue;
            int g=gcd(x,y);
            int sx=x/g,sy=y/g;
            int sq=sx*sx+sy*sy;
            int k=1;
            while(k*k*sq<d*d)k++;
            int r=g-k*(t-1);
            if(r>=0){
                int cnt=c[r+t-2][t-2];
                int m=(w-x+1)*(h-y+1)%1000000000;
                if(x>0&&y>0)m=m*2%1000000000;
                ans=(ans+cnt*m)%1000000000;
            }
        }
    }
    cout<<ans;
}