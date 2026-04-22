#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define f first
#define s second
using p=pair<int,int>;
int n,s;
int a[45];
vector<int> l,r;
void dfs1(int idx,int sum){
	if(idx==n/2){
		l.push_back(sum);
		return;
	}
	dfs1(idx+1,sum+a[idx]);
	dfs1(idx+1,sum);
}
void dfs2(int idx,int sum){
	if(idx==n) r.push_back(sum);
	else{
		dfs2(idx+1,sum+a[idx]);
		dfs2(idx+1,sum);
	}
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>s;
	for(int i=0;i<n;i++)cin>>a[i];
	dfs1(0,0);
	dfs2(n/2,0);
	sort(l.begin(),l.end());
	sort(r.begin(),r.end());
	int pt1=0,pt2=r.size()-1;
	int ans=0;
	while(pt1<l.size()&&pt2>=0){
		int lv=l[pt1],rv=r[pt2];
		if(lv+rv==s){
			int lc=0,rc=0;
			while(pt1<l.size()&&l[pt1]==lv){
				lc++;
				pt1++;
			}
			while(pt2>=0&&r[pt2]==rv) rc++,pt2--;
			ans+=lc*rc;
		}else if(lv+rv<s){
			pt1++;
		}
		else pt2--;
	}
	if(s==0) ans--;
	cout<<ans;
}