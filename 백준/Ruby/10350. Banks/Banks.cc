#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> a(n+1,0);
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        a[i]=a[i-1]+k;
    }
    int sum=a[n],ans=0;
    for(int i=1;i<=n;i++){
        for(int r=1;r<=n;r++){
            int d=a[i]-a[r]-1;
            int c=(d>=0)?(d/sum):((d-sum+1)/sum);
            if(r>i)c++;
            if(c>0)ans+=c;
        }
    }
    cout<<ans;
}