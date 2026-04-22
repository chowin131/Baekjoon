#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define f first
#define s second
using p=pair<int,int>;
string str;
int n;
int dp[55][55];
int solve(int l,int r,string& S){
	if(l>=r) return 0;
	if(dp[l][r]!=-1) return dp[l][r];
	int res=solve(l+1,r,S)+1;
	res=min(res,solve(l,r-1,S)+1);
	res=min(res,solve(l+1,r-1,S)+1);
	if(S[l]==S[r]){
		res=min(res,solve(l+1,r-1,S));
	}
	return dp[l][r]=res;
}
int get_dp(string& S){
	memset(dp,-1,sizeof(dp));
	return solve(0,n-1,S);
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>str;
	n=str.length();
	int ans=get_dp(str);
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(str[i]==str[j]) continue;
			swap(str[i],str[j]);
			ans=min(ans,get_dp(str)+1);
			swap(str[i],str[j]);
		}
	}
	cout<<ans;
}