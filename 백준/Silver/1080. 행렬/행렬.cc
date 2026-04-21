#include <bits/stdc++.h>
using namespace std;
string a[55],b[55];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;++i)cin>>a[i];
    for(int i=0;i<n;++i)cin>>b[i];
    int ans=0;
    for(int i=0;i<=n-3;++i)
        for(int j=0;j<=m-3;++j)
            if(a[i][j]!=b[i][j]){
                ans++;
                for(int r=0;r<3;++r)
                    for(int c=0;c<3;++c)
                        a[i+r][j+c]=(a[i+r][j+c]=='0'?'1':'0');
            }
    for(int i=0;i<n;++i)
        if(a[i]!=b[i])
            return cout<<-1<<'\n',0;
    cout<<ans<<'\n';
}