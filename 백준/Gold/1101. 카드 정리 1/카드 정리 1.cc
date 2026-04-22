#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define f first
#define s second
using p=pair<int,int>;
int n,m;
int a[55][55];
int cnt[55],c[55];
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]>0){
				cnt[i]++;
				c[i]=j;
			}
		}
	}
	
	int ans=1e18;
	for(int j=1;j<=n;j++){
		int k=0;
		set<int> st;
		for(int i=1;i<=n;i++){
			if(i==j)continue;
			if(cnt[i]>0){
				k++;
			}
			if(cnt[i]==1)st.insert(c[i]);
		}
		int cur=k-st.size();
		if(cur<ans)ans=cur;
	}
	cout<<ans<<"\n";
	return 0;
}