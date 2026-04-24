#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p = pair<int,int>;
#define f first
#define s second
const int MOD=998244353;
int dp[9][105][105];
int ndp[9][105][105];
char a[105][105];
int dr[8]={-1,-1,0,1,1,1,0,-1};
int dc[8]={0,1,1,1,0,-1,-1,-1};
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i){
        string str;
        cin>>str;
        for(int j=1;j<=m;++j)a[i][j]=str[j-1];
    }
    int rs,cs,re,ce;cin>>rs>>cs>>re>>ce;
    dp[8][rs][cs]=1;
    for(int step=1;step<=k;++step){
        int sum_all[105][105]={0};
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                for(int pd=0;pd<=8;++pd)
                    sum_all[i][j]=(sum_all[i][j]+dp[pd][i][j])%MOD;
        for(int d=0;d<8;++d){
            int is=dr[d]>=0?1:n,ie=dr[d]>=0?n:1,ist=dr[d]>=0?1:-1;
            int js=dc[d]>=0?1:m,je=dc[d]>=0?m:1,jst=dc[d]>=0?1:-1;
            for(int i=is;ist==1?i<=ie:i>=ie;i+=ist){
                for(int j=js;jst==1?j<=je:j>=je;j+=jst){
                    if(a[i][j]=='#') ndp[d][i][j]=0;
                    else{
                        int pi=i-dr[d],pj=j-dc[d];
                        if(pi>=1&&pi<=n&&pj>=1&&pj<=m&&a[pi][pj]!='#'){
                            ndp[d][i][j]=(ndp[d][pi][pj]+(sum_all[pi][pj]-dp[d][pi][pj]+MOD)%MOD)%MOD;
                        }
                        else ndp[d][i][j]=0;
                    }
                }
            }
        }
        for(int d=0;d<8;++d)
            for(int i=1;i<=n;++i)
                for(int j=1;j<=m;++j)
                    dp[d][i][j]=ndp[d][i][j];
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                dp[8][i][j]=0;
    }
    int ans=0;
    for(int d=0;d<8;++d) ans=(ans+dp[d][re][ce])%MOD;
    cout<<ans;
}