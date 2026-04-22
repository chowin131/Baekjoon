#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define f first
#define s second
using p=pair<int,int>;
int n;
vector<p> adj[100005];
int mx,mx_idx;
void dfs(int cur,int p,int d){
	if(d>mx){
		mx=d;
		mx_idx=cur;
	}
	for(auto nxt:adj[cur]){
		if(nxt.f!=p)dfs(nxt.f,cur,d+nxt.s);
	}
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=0;i<n;i++){
		int u;
		cin>>u;
		while(1){
			int v;
			cin>>v;
			if(v==-1)break;
			int w;
			cin>>w;
			adj[u].push_back({v,w});
		}
	}
	mx=0;
	mx_idx=1;
	dfs(1,0,0);
	mx=0;
	dfs(mx_idx,0,0);
	cout<<mx;
}