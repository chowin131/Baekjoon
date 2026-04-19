#include<bits/stdc++.h>
using namespace std;
#define int long long
int pmod(int x,int y,int m){
	int r=1;x%=m;
	while(y){
		if(y&1)r=(__int128)r*x%m;
		x=(__int128)x*x%m;
		y>>=1;
	}
	return r;
}
bool mr(int n,int a){
	if(n%a==0)return 0;
	int d=n-1;
	while(d%2==0)d>>=1;
	int t=pmod(a,d,n);
	if(t==1||t==n-1)return 1;
	while(d!=n-1){
		t=(__int128)t*t%n;
		d<<=1;
		if(t==n-1)return 1;
	}
	return 0;
}
bool is_p(int n){
	if(n<=1)return 0;
	if(n==2||n==3)return 1;
	if(n%2==0)return 0;
	for(int i:{2,3,5,7,11,13,17,19,23,29,31,37}){
		if(n==i)return 1;
		if(!mr(n,i))return 0;
	}
	return 1;
}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
vector<int> ans;
void go(int n){
	if(n<=1)return;
	if(n%2==0){ans.push_back(2);go(n/2);return;}
	if(is_p(n)){ans.push_back(n);return;}
	int x,y,c,g=n;
	while(g==n){
		x=rand()%(n-2)+2;y=x;c=rand()%(n-1)+1;g=1;
		while(g==1){
			x=((__int128)x*x%n+c)%n;
			y=((__int128)y*y%n+c)%n;
			y=((__int128)y*y%n+c)%n;
			g=gcd(x>y?x-y:y-x,n);
		}
	}
	go(g);go(n/g);
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n;
    cin>>n;
	go(n);
	sort(ans.begin(),ans.end());
	for(int i:ans)cout<<i<<'\n';
}