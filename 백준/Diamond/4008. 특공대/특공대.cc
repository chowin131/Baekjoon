#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a,b,c,s[1000005],dp[1000005];
struct L{
	int m,k;
	double x(L o){return (double)(k-o.k)/(o.m-m);}
}q[1000005];

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>a>>b>>c;
	for(int i=1;i<=n;i++){
		int v;
		cin>>v;
		s[i]=s[i-1]+v;
	}
	int h=0,t=0;
	q[t++]={0,0};
	for(int i=1;i<=n;i++){
		while(h+1<t&&q[h].x(q[h+1])<=s[i])h++;
		dp[i]=q[h].m*s[i]+q[h].k+a*s[i]*s[i]+b*s[i]+c;
		L cur={-2*a*s[i],dp[i]+a*s[i]*s[i]-b*s[i]};
		while(h+1<t&&q[t-2].x(q[t-1])>=q[t-1].x(cur))t--;
		q[t++]=cur;
	}
	cout<<dp[n];
}