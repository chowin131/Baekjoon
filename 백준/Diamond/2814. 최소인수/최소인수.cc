#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,p,ans;
bitset<2000005> ip;
vector<int> pr;
int phi(int x,int a){
	if(x==0)return 0;
	if(a<0)return x;
	if(pr[a]*pr[a]>=x)return max(1LL,(int)(upper_bound(pr.begin(),pr.end(),x)-pr.begin())-a);
	return phi(x,a-1)-phi(x/pr[a],a-1);
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>p;
	if(p>31622){
		if(n==1)cout<<p;
		else cout<<0;
		return 0;
	}
	ip.set();
	ip[0]=ip[1]=0;
	for(int i=2;i*i<2000005;i++){
		if(ip[i])for(int j=i*i;j<2000005;j+=i)ip[j]=0;
	}
	for(int i=2;i<2000005;i++)if(ip[i])pr.push_back(i);
	int l=1,r=1000000000/p;
	int a=upper_bound(pr.begin(),pr.end(),p-1)-pr.begin()-1;
	while(l<=r){
		int m=(l+r)/2;
		if(phi(m,a)>=n){
			ans=m;
			r=m-1;
		}else l=m+1;
	}
	if(ans==0)cout<<0;
	else cout<<ans*p;
}