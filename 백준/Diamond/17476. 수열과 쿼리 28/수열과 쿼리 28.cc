#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
int n,m,a[100005],ts[400005],tmx[400005],tmn[400005],lz[400005];
void up(int nd){
	ts[nd]=ts[nd*2]+ts[nd*2+1];
	tmx[nd]=max(tmx[nd*2],tmx[nd*2+1]);
	tmn[nd]=min(tmn[nd*2],tmn[nd*2+1]);
}
void app(int nd,int l,int r,int v){
	ts[nd]+=v*(r-l+1);
	tmx[nd]+=v;
	tmn[nd]+=v;
	lz[nd]+=v;
}
void down(int nd,int l,int r){
	if(!lz[nd])return;
	int mid=(l+r)/2;
	app(nd*2,l,mid,lz[nd]);
	app(nd*2+1,mid+1,r,lz[nd]);
	lz[nd]=0;
}
void init(int nd,int l,int r){
	if(l==r){
		ts[nd]=tmx[nd]=tmn[nd]=a[l];
		return;
	}
	int mid=(l+r)/2;
	init(nd*2,l,mid);
	init(nd*2+1,mid+1,r);
	up(nd);
}
void uadd(int nd,int l,int r,int ql,int qr,int v){
	if(qr<l||r<ql)return;
	if(ql<=l&&r<=qr){
		app(nd,l,r,v);
		return;
	}
	down(nd,l,r);
	int mid=(l+r)/2;
	uadd(nd*2,l,mid,ql,qr,v);
	uadd(nd*2+1,mid+1,r,ql,qr,v);
	up(nd);
}
void usqrt(int nd,int l,int r,int ql,int qr){
	if(qr<l||r<ql)return;
	if(ql<=l&&r<=qr){
		int sqx=floor(sqrt(tmx[nd]));
		int sqn=floor(sqrt(tmn[nd]));
		if(tmx[nd]-tmn[nd]==sqx-sqn){
			app(nd,l,r,sqx-tmx[nd]);
			return;
		}
	}
	down(nd,l,r);
	int mid=(l+r)/2;
	usqrt(nd*2,l,mid,ql,qr);
	usqrt(nd*2+1,mid+1,r,ql,qr);
	up(nd);
}
int qsum(int nd,int l,int r,int ql,int qr){
	if(qr<l||r<ql)return 0;
	if(ql<=l&&r<=qr)return ts[nd];
	down(nd,l,r);
	int mid=(l+r)/2;
	return qsum(nd*2,l,mid,ql,qr)+qsum(nd*2+1,mid+1,r,ql,qr);
}
main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	init(1,1,n);
	cin>>m;
	while(m--){
		int op,l,r;
        cin>>op>>l>>r;
		if(op==1){
			int x;
            cin>>x;
			uadd(1,1,n,l,r,x);
		}
        else if(op==2)usqrt(1,1,n,l,r);
		else cout<<qsum(1,1,n,l,r)<<"\n";
	}
}