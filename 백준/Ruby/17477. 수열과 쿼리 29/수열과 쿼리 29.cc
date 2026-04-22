#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define f first
#define s second
using p=pair<int,int>;

const int MAX=500005;
const int INF=2e18;

int n,m;
int a[MAX];
int mx[MAX*4],smx[MAX*4],mxc[MAX*4];
int mn[MAX*4],smn[MAX*4],mnc[MAX*4];
int sumB[MAX*4],sz[MAX*4];
int add_A_mx[MAX*4],add_A_mn[MAX*4],add_A_o[MAX*4];
int add_B_mx[MAX*4],add_B_mn[MAX*4],add_B_o[MAX*4];

void pull(int u){
	int l=u*2,r=u*2+1;
	sumB[u]=sumB[l]+sumB[r];
	
	if(mx[l]==mx[r]){
		mx[u]=mx[l];
		mxc[u]=mxc[l]+mxc[r];
		smx[u]=max(smx[l],smx[r]);
	}else if(mx[l]>mx[r]){
		mx[u]=mx[l];
		mxc[u]=mxc[l];
		smx[u]=max(smx[l],mx[r]);
	}
	else{
		mx[u]=mx[r];
		mxc[u]=mxc[r];
		smx[u]=max(mx[l],smx[r]);
	}
	
	if(mn[l]==mn[r]){
		mn[u]=mn[l];
		mnc[u]=mnc[l]+mnc[r];
		smn[u]=min(smn[l],smn[r]);
	}
	else if(mn[l]<mn[r]){
		mn[u]=mn[l];
		mnc[u]=mnc[l];
		smn[u]=min(smn[l],mn[r]);
	}else{
		mn[u]=mn[r];
		mnc[u]=mnc[r];
		smn[u]=min(mn[l],smn[r]);
	}
}

void apply(int u,int A_mx,int A_mn,int A_o,int B_mx,int B_mn,int B_o){
	if(mx[u]==mn[u]){
		sumB[u]+=B_mx*sz[u];
		mx[u]+=A_mx;
		mn[u]+=A_mx;
		add_A_mx[u]+=A_mx;
		add_A_mn[u]+=A_mx;
		add_B_mx[u]+=B_mx;
		add_B_mn[u]+=B_mx;
	}
    else{
		sumB[u]+=B_mx*mxc[u]+B_mn*mnc[u]+B_o*(sz[u]-mxc[u]-mnc[u]);
		
		int old_mx=mx[u],old_mn=mn[u];
		if(smx[u]==old_mn)smx[u]+=A_mn;
		else if(smx[u]!=-INF)smx[u]+=A_o;
		
		if(smn[u]==old_mx)smn[u]+=A_mx;
		else if(smn[u]!=INF)smn[u]+=A_o;
		
		mx[u]+=A_mx;
		mn[u]+=A_mn;
		
		add_A_mx[u]+=A_mx;
		add_A_mn[u]+=A_mn;
		add_A_o[u]+=A_o;
		add_B_mx[u]+=B_mx;
		add_B_mn[u]+=B_mn;
		add_B_o[u]+=B_o;
	}
}

void push(int u){
	int old_mx=mx[u]-add_A_mx[u];
	int old_mn=mn[u]-add_A_mn[u];
	
	for(int c:{u*2,u*2+1}){
		int c_A_mx=add_A_o[u],c_A_mn=add_A_o[u],c_A_o=add_A_o[u];
		int c_B_mx=add_B_o[u],c_B_mn=add_B_o[u],c_B_o=add_B_o[u];
		
		if(mx[c]==old_mx){
			c_A_mx=add_A_mx[u];
			c_B_mx=add_B_mx[u];
		}
		else if(mx[c]==old_mn){
			c_A_mx=add_A_mn[u];
			c_B_mx=add_B_mn[u];
		}
		
		if(mn[c]==old_mx){
			c_A_mn=add_A_mx[u];
			c_B_mn=add_B_mx[u];
		}else if(mn[c]==old_mn){
			c_A_mn=add_A_mn[u];
			c_B_mn=add_B_mn[u];
		}
		
		apply(c,c_A_mx,c_A_mn,c_A_o,c_B_mx,c_B_mn,c_B_o);
	}
	
	add_A_mx[u]=add_A_mn[u]=add_A_o[u]=0;
	add_B_mx[u]=add_B_mn[u]=add_B_o[u]=0;
}

void build(int u,int l,int r){
	sz[u]=r-l+1;
	if(l==r){
		mx[u]=mn[u]=a[l];
		mxc[u]=mnc[u]=1;
		smx[u]=-INF;
		smn[u]=INF;
		sumB[u]=0;
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	pull(u);
}

void up_add(int u,int l,int r,int ql,int qr,int x){
	if(l>qr||r<ql)return;
	if(ql<=l&&r<=qr){
		int b=(x!=0?1:0);
		apply(u,x,x,x,b,b,b);
		return;
	}
	push(u);
	int mid=(l+r)/2;
	up_add(u*2,l,mid,ql,qr,x);
	up_add(u*2+1,mid+1,r,ql,qr,x);
	pull(u);
}

void up_chmax(int u,int l,int r,int ql,int qr,int y){
	if(l>qr||r<ql||mn[u]>=y)return;
	if(ql<=l&&r<=qr&&smn[u]>y){
		int diff=y-mn[u];
		int a_mx=(mx[u]==mn[u]?diff:0);
		int b_mx=(mx[u]==mn[u]?1:0);
		apply(u,a_mx,diff,0,b_mx,1,0);
		return;
	}
	push(u);
	int mid=(l+r)/2;
	up_chmax(u*2,l,mid,ql,qr,y);
	up_chmax(u*2+1,mid+1,r,ql,qr,y);
	pull(u);
}

void up_chmin(int u,int l,int r,int ql,int qr,int y){
	if(l>qr||r<ql||mx[u]<=y)return;
	if(ql<=l&&r<=qr&&smx[u]<y){
		int diff=y-mx[u];
		int a_mn=(mx[u]==mn[u]?diff:0);
		int b_mn=(mx[u]==mn[u]?1:0);
		apply(u,diff,a_mn,0,1,b_mn,0);
		return;
	}
	push(u);
	int mid=(l+r)/2;
	up_chmin(u*2,l,mid,ql,qr,y);
	up_chmin(u*2+1,mid+1,r,ql,qr,y);
	pull(u);
}

int qry(int u,int l,int r,int ql,int qr){
	if(l>qr||r<ql)return 0;
	if(ql<=l&&r<=qr)return sumB[u];
	push(u);
	int mid=(l+r)/2;
	return qry(u*2,l,mid,ql,qr)+qry(u*2+1,mid+1,r,ql,qr);
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
			up_add(1,1,n,l,r,v);
		}else if(op==2){
			cin>>v;
			up_chmax(1,1,n,l,r,v);
		}
		else if(op==3){
			cin>>v;
			up_chmin(1,1,n,l,r,v);
		}else{
			cout<<qry(1,1,n,l,r)<<"\n";
		}
	}
	return 0;
}