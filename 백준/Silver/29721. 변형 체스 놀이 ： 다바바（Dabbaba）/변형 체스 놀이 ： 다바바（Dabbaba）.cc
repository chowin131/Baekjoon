#include <bits/stdc++.h>
using namespace std;
#define int long long
using p=pair<int,int>;
#define f first
#define s second
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,k;cin>>n>>k;
    vector<p> v(k);
    for(int i=0;i<k;++i)cin>>v[i].f>>v[i].s;
    sort(v.begin(),v.end());
    vector<p> ans;
    int dx[]={-2,2,0,0},dy[]={0,0,-2,2};
    for(auto pt:v)
        for(int i=0;i<4;++i){
            int nx=pt.f+dx[i],ny=pt.s+dy[i];
            if(1<=nx&&nx<=n&&1<=ny&&ny<=n)
                if(!binary_search(v.begin(),v.end(),make_pair(nx,ny)))ans.push_back({nx,ny});
        }
    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    cout<<ans.size();
}