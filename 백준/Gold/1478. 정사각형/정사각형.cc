#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
int n;
map<int,vector<p>> rv,rh,vs,hs;
vector<int> ux,uy;
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=0;i<n;i++){
		int x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
		rv[x1].push_back({y1,y2});
		rv[x2].push_back({y1,y2});
		rh[y1].push_back({x1,x2});
		rh[y2].push_back({x1,x2});
	}
	for(auto& kv:rv){
		ux.push_back(kv.f);
		auto& rw=kv.s;
		sort(rw.begin(),rw.end());
		int st=rw[0].f,en=rw[0].s;
		for(int i=1;i<rw.size();i++){
			if(rw[i].f<=en)en=max(en,rw[i].s);
			else{
				vs[kv.f].push_back({st,en});
				st=rw[i].f;
				en=rw[i].s;
			}
		}
		vs[kv.f].push_back({st,en});
	}
	for(auto& kv:rh){
		uy.push_back(kv.f);
		auto& rw=kv.s;
		sort(rw.begin(),rw.end());
		int st=rw[0].f,en=rw[0].s;
		for(int i=1;i<rw.size();i++){
			if(rw[i].f<=en)en=max(en,rw[i].s);
			else{
				hs[kv.f].push_back({st,en});
				st=rw[i].f;
				en=rw[i].s;
			}
		}
		hs[kv.f].push_back({st,en});
	}
	int ans=0;
	auto cv=[](const vector<p>& sg,int a,int b){
		for(auto& x:sg)if(x.f<=a&&b<=x.s)return true;
		return false;
	};
	for(int i=0;i<ux.size();i++){
		for(int j=i+1;j<ux.size();j++){
			int l=ux[j]-ux[i];
			for(int k=0;k<uy.size();k++){
				int yb=uy[k],yt=yb+l;
				if(!binary_search(uy.begin(),uy.end(),yt))continue;
				if(!cv(vs[ux[i]],yb,yt))continue;
				if(!cv(vs[ux[j]],yb,yt))continue;
				if(!cv(hs[yb],ux[i],ux[j]))continue;
				if(!cv(hs[yt],ux[i],ux[j]))continue;
				ans++;
			}
		}
	}
	cout<<ans;
}