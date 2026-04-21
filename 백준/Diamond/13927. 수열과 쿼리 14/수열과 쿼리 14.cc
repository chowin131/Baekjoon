#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

struct Node{int32_t l,r,sum;}nodes[60000005];
int32_t cnt=0,n,U,m;
int a[100005],v[100005];
int32_t c[100005],prv[100005],lp[100005];
vector<int32_t> I[500005],rt[500005];

int32_t upd(int32_t p,int32_t tl,int32_t tr,int32_t pos){
	int32_t cur=++cnt;
	nodes[cur]=nodes[p];
	nodes[cur].sum++;
	if(tl==tr)return cur;
	int32_t tm=tl+(tr-tl)/2;
	if(pos<=tm)nodes[cur].l=upd(nodes[p].l,tl,tm,pos);
	else nodes[cur].r=upd(nodes[p].r,tm+1,tr,pos);
	return cur;
}

int32_t qry(int32_t root,int32_t tl,int32_t tr,int32_t limit){
	if(!root)return 0;
	if(tr<=limit)return nodes[root].sum;
	int32_t tm=tl+(tr-tl)/2;
	if(limit<=tm)return qry(nodes[root].l,tl,tm,limit);
	else return nodes[nodes[root].l].sum+qry(nodes[root].r,tm+1,tr,limit);
}

void ins(int32_t node,int32_t l,int32_t r,int32_t val,int32_t idx,int32_t p){
	I[node].push_back(idx);
	int32_t prt=rt[node].empty()?0:rt[node].back();
	rt[node].push_back(upd(prt,0,n,p));
	if(l==r)return;
	int32_t tm=l+(r-l)/2;
	if(val<=tm)ins(node*2,l,tm,val,idx,p);
	else ins(node*2+1,tm+1,r,val,idx,p);
}

int32_t get_c(int32_t node,int32_t L,int32_t R){
	if(I[node].empty())return 0;
	auto it=upper_bound(I[node].begin(),I[node].end(),R);
	if(it==I[node].begin())return 0;
	int32_t idx=it-I[node].begin()-1;
	int32_t cntR=qry(rt[node][idx],0,n,L-1);
	int32_t cntL=lower_bound(I[node].begin(),I[node].end(),L)-I[node].begin();
	return cntR-cntL;
}

int solve(int L,int R,int K){
	if(K>get_c(1,L,R))return -1;
	int32_t cur=1,l=1,r=U;
	while(l<r){
		int32_t tm=l+(r-l)/2;
		int32_t c=get_c(cur*2,L,R);
		if(K<=c){cur=cur*2;r=tm;}
		else{K-=c;cur=cur*2+1;l=tm+1;}
	}
	return v[l];
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	vector<int> vals;
	for(int i=1;i<=n;++i){cin>>a[i];vals.push_back(a[i]);}
	sort(vals.begin(),vals.end());
	vals.erase(unique(vals.begin(),vals.end()),vals.end());
	U=vals.size();
	for(int i=1;i<=U;++i)v[i]=vals[i-1];
	for(int i=1;i<=n;++i)c[i]=lower_bound(vals.begin(),vals.end(),a[i])-vals.begin()+1;
	for(int i=1;i<=n;++i){
		prv[i]=lp[c[i]];
		lp[c[i]]=i;
		ins(1,1,U,c[i],i,prv[i]);
	}
	cin>>m;
	int ans=0;
	for(int i=0;i<m;++i){
		int x,y,z,w,k;
		cin>>x>>y>>z>>w>>k;
		int L=(x*max(ans,0LL)+y)%n+1;
		int R=(z*max(ans,0LL)+w)%n+1;
		if(L>R)swap(L,R);
		ans=solve(L,R,k);
		cout<<ans<<"\n";
	}
}