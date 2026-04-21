#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

const int B=400;
int a[100005];
vector<int> b[305];

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>a[i];
        b[i/B].push_back(a[i]);
    }
    for(int i=0;i<=n/B;++i)sort(b[i].begin(),b[i].end());
    int m;cin>>m;
    while(m--){
        int t;cin>>t;
        if(t==1){
            int l,r,k;cin>>l>>r>>k;l--;r--;
            int lb=l/B,rb=r/B,cnt=0;
            if(lb==rb)for(int i=l;i<=r;++i){if(a[i]>k)cnt++;}
            else{
                for(int i=l;i<(lb+1)*B;++i)if(a[i]>k)cnt++;
                for(int i=lb+1;i<rb;++i)cnt+=b[i].end()-upper_bound(b[i].begin(),b[i].end(),k);
                for(int i=rb*B;i<=r;++i)if(a[i]>k)cnt++;
            }
            cout<<cnt<<'\n';
        }
        else{
            int i,k;cin>>i>>k;i--;
            int bb=i/B;
            b[bb].erase(lower_bound(b[bb].begin(),b[bb].end(),a[i]));
            a[i]=k;
            b[bb].insert(lower_bound(b[bb].begin(),b[bb].end(),a[i]),a[i]);
        }
    }
    return 0;
}