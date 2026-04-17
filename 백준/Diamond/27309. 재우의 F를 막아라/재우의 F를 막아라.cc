#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=998244353;
int power(int base,int exp){
    int res=1;
    base%=MOD;
    while(exp>0){
        if(exp%2==1)res=(res*base)%MOD;
        base=(base*base)%MOD;
        exp/=2;
    }
    return res;
}
int R(int q,int N){
    if(q%(2*N)==0)return N;
    if(q%2!=0)return 1;
    return 0;
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int N,d;
    if(!(cin>>N>>d))return 0;
    if(d==1){
        cout<<1<<"\n";
        return 0;
    }
    int K=d-1;
    int A=(N-3+MOD)%MOD;
    vector<int> dp(K+2,0),next_dp(K+2,0);
    dp[0]=1;
    for(int k=1;k<=K;k++){
        for(int q=0;q<=k;q++)
            next_dp[q]=(A*dp[q]+dp[abs(q-1)]+dp[q+1])%MOD;
        for(int q=0;q<=k;q++)dp[q]=next_dp[q];
    }
    int trace=(dp[0]*R(0,N))%MOD;
    for(int q=1;q<=K;q++)
        trace=(trace+(2*dp[q]%MOD)*R(q,N))%MOD;
    cout<<(trace*power(N,K-1))%MOD<<"\n";
}