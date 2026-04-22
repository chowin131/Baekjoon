#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define f first
#define s second
using p=pair<int,int>;
int n,m;
int a[200005];
int mx[800005],v_and[800005],v_or[800005],lz[800005];
void apply(int u,int val){
	mx[u]+=val;
	v_and[u]+=val;
	v_or[u]+=val;
	lz[u]+=val;
}
void push(int u){
	if(lz[u]){
		apply(u*2,lz[u]);
		apply(u*2+1,lz[u]);
		lz[u]=0;
	}
}
void pull(int u){
	mx[u]=max(mx[u*2],mx[u*2+1]);
	v_and[u]=v_and[u*2]&v_and[u*2+1];
	v_or[u]=v_or[u*2]|v_or[u*2+1];
}
void build(int u,int l,int r){
	if(l==r){
		mx[u]=v_and[u]=v_or[u]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	pull(u);
}
void up_and(int u,int l,int r,int ql,int qr,int x){
	if(l>qr||r<ql)return;
	if(ql<=l&&r<=qr){
		int mask=(~x)&v_or[u];
		if(((v_or[u]^v_and[u])&mask)==0){
			apply(u,-mask);
			return;
		}
	}
	
	push(u);
	int mid=(l+r)/2;
	up_and(u*2,l,mid,ql,qr,x);
	up_and(u*2+1,mid+1,r,ql,qr,x);
	pull(u);
}

void up_or(int u,int l,int r,int ql,int qr,int x){
	if(l>qr||r<ql)return;
	if(ql<=l&&r<=qr){
		int mask=x&(~v_and[u]);
		if(((v_or[u]^v_and[u])&mask)==0){
			apply(u,mask);
			return;
		}
	}
	push(u);
	int mid=(l+r)/2;
	up_or(u*2,l,mid,ql,qr,x);
	up_or(u*2+1,mid+1,r,ql,qr,x);
	pull(u);
}

int qry(int u,int l,int r,int ql,int qr){
	if(l>qr||r<ql)return 0;
	if(ql<=l&&r<=qr)return mx[u];
	push(u);
	int mid=(l+r)/2;
	return max(qry(u*2,l,mid,ql,qr),qry(u*2+1,mid+1,r,ql,qr));
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	cin>>m;
	while(m--){
		int op,l,r,x;
		cin>>op>>l>>r;
		if(op==1){
			cin>>x;
			up_and(1,1,n,l,r,x);
		}else if(op==2){
			cin>>x;
			up_or(1,1,n,l,r,x);
		}
		else{
			cout<<qry(1,1,n,l,r)<<"\n";
		}
	}
}