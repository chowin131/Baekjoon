#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define f first
#define s second
using p=pair<int,int>;
const int MAX=1000005;
int n,m;
int a[MAX];
int mx[MAX*4],smx[MAX*4],cnt[MAX*4],sum[MAX*4];
void pull(int u){
	int l=u*2,r=u*2+1;
	sum[u]=sum[l]+sum[r];
	if(mx[l]==mx[r]){
		mx[u]=mx[l];
		cnt[u]=cnt[l]+cnt[r];
		smx[u]=max(smx[l],smx[r]);
	}
    else if(mx[l]>mx[r]){
		mx[u]=mx[l];
		cnt[u]=cnt[l];
		smx[u]=max(smx[l],mx[r]);
	}
	else{
		mx[u]=mx[r];
		cnt[u]=cnt[r];
		smx[u]=max(mx[l],smx[r]);
	}
}
void push(int u){
	int l=u*2,r=u*2+1;
	if(mx[l]>mx[u]){
		sum[l]-=(mx[l]-mx[u])*cnt[l];
		mx[l]=mx[u];
	}
	if(mx[r]>mx[u])sum[r]-=(mx[r]-mx[u])*cnt[r],mx[r]=mx[u];
}
void build(int u,int l,int r){
	if(l==r){
		mx[u]=sum[u]=a[l];
		smx[u]=-1;
		cnt[u]=1;
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	pull(u);
}

void upd(int u,int l,int r,int ql,int qr,int v){
	if(l>qr||r<ql||mx[u]<=v)return;
	if(ql<=l&&r<=qr&&smx[u]<v){
		sum[u]-=(mx[u]-v)*cnt[u];
		mx[u]=v;
		return;
	}
	push(u);
	int mid=(l+r)/2;
	upd(u*2,l,mid,ql,qr,v);
	upd(u*2+1,mid+1,r,ql,qr,v);
	pull(u);
}
int q_max(int u,int l,int r,int ql,int qr){
	if(l>qr||r<ql)return -1;
	if(ql<=l&&r<=qr)return mx[u];
	push(u);
	int mid=(l+r)/2;
	return max(q_max(u*2,l,mid,ql,qr),q_max(u*2+1,mid+1,r,ql,qr));
}
int q_sum(int u,int l,int r,int ql,int qr){
	if(l>qr||r<ql)return 0;
	if(ql<=l&&r<=qr){
		return sum[u];
	}
	push(u);
	int mid=(l+r)/2;
	return q_sum(u*2,l,mid,ql,qr)+q_sum(u*2+1,mid+1,r,ql,qr);
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	cin>>m;
	while(m--){
		int op,l,r,v;
		cin>>op>>l>>r;
		if(op==1){
			cin>>v;
			upd(1,1,n,l,r,v);
		}
		else if(op==2)cout<<q_max(1,1,n,l,r)<<"\n";
		else{
			cout<<q_sum(1,1,n,l,r)<<"\n";
		}
	}
}