#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
uint64_t S[26][785],d[785];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    string s1,s2;
    cin>>s1>>s2;
    int n=s1.size(),m=s2.size();
    for(int i=0;i<m;i++)S[s2[i]-'A'][i/64]|=1ULL<<(i%64);
    for(int i=0;i<n;i++){
        int c=s1[i]-'A';
        uint64_t b=0,sh=1;
        for(int j=0;j<=m/64;j++){
            uint64_t x=d[j];
            uint64_t u=x|S[c][j];
            uint64_t v=(x<<1)|sh;
            sh=x>>63;
            uint64_t sub=u-v-b;
            if(u<v)b=1;
            else if(u==v&&b==1)b=1;
            else b=0;
            d[j]=u&~sub;
        }
    }
    int ans=0;
    for(int i=0;i<=m/64;i++)ans+=__builtin_popcountll(d[i]);
    cout<<ans;
}