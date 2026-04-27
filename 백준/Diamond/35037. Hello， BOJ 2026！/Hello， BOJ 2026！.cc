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
    vector<bitset<2000>> adj(n);
    vector<int> d(n,0);
    vector<p> edges;
    int E=0;
    for(int i=0;i<n-1;++i){
        string str;
        cin>>str;
        for(int j=0;j<str.length();++j)
            if(str[j]=='1'){
                adj[i][i+1+j]=1;
                adj[i+1+j][i]=1;
                d[i]++;
                d[i+1+j]++;
                edges.push_back({i,i+1+j});
                E++;
            }
    }
    auto C=[&](int x,int k){
        if(x<k) return 0LL;
        return (x&k)==k?1LL:0LL;
    };
    int cp3=0,cst=0;
    for(int i=0;i<n;++i){
        cp3^=C(d[i],2);
        cst^=C(d[i],3);
    }
    int w=0,ck3=0;
    for(auto e:edges){
        int u=e.f,v=e.s;
        w^=(d[u]%2==0&&d[v]%2==0);
        ck3^=(adj[u]&adj[v]).count()%2;
    }
    cout<<(C(n,4)^((E%2)*C(n-2,2))^(cp3*C(n-3,1))^(C(E,2)^cp3)^cst^w^ck3);
}