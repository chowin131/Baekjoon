#include <bits/stdc++.h>
using namespace std;
#define int long long
using p=pair<int,int>;
#define f first
#define s second
int M1=1e9+7,M2=1e9+9;
int B1=313,B2=317;
int P1[1000005],P2[1000005],H1[1000005],H2[1000005];
p get_hash(int l,int r){
    l++,r++;
    int h1=(H1[r]-H1[l-1]*P1[r-l+1])%M1;
    if(h1<0) h1+=M1;
    int h2=(H2[r]-H2[l-1]*P2[r-l+1])%M2;
    if(h2<0) h2+=M2;
    return {h1,h2};
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    string t;
    cin>>n>>t;
    P1[0]=P2[0]=1;
    for(int i=1;i<=n;i++){
        P1[i]=(P1[i-1]*B1)%M1;
        P2[i]=(P2[i-1]*B2)%M2;
        H1[i]=(H1[i-1]*B1+t[i-1])%M1;
        H2[i]=(H2[i-1]*B2+t[i-1])%M2;
    }
    vector<bool> v(n/2+1,false);
    v[0]=true;
    for(int i=1;i<=n/2;i++)
        if(get_hash(0,i-1)==get_hash(n-i,n-1)) v[i]=true;
    vector<int> L(n/2+2,0);
    for(int i=n/2;i>=0;i--){
        int c=L[i+1]+2;
        c=min(c,n/2-i);
        while(c>0){
            if(get_hash(i,i+c-1)==get_hash(n-i-c,n-i-1)) break;
            c--;
        }
        L[i]=c;
    }
    int m=0;
    for(int i=0;i<=n/2;i++) if(v[i]) m=max(m,i+L[i]);
    cout<<m;
}