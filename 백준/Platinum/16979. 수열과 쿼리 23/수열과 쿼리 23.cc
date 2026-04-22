#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define f first
#define s second
using p=pair<int,int>;
int n,m,sq;
int a[100005],b[100005],bit[100005],ans[100005];
struct Q{
	int l,r,id;
}q[100005];
bool cmp(Q x,Q y){
	if(x.l/sq!=y.l/sq)return x.l/sq<y.l/sq;
	if((x.l/sq)&1)return x.r<y.r;
	else{
		return x.r>y.r;
	}
}
void add(int i,int v){
	for(;i<=n;i+=i&-i)bit[i]+=v;
}
int sum(int i){
	int ret=0;
	for(;i>0;i-=i&-i){
		ret+=bit[i];
	}
	return ret;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	sq=sqrt(n);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	
	sort(b+1,b+n+1);
	int len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	
	int l=q[1].l,r=q[1].l-1,cur=0;
	for(int i=1;i<=m;i++){
		while(l>q[i].l){
			l--;
			cur+=sum(a[l]-1);
			add(a[l],1);
		}
		while(r<q[i].r){
			r++;
			cur+=sum(n)-sum(a[r]);
			add(a[r],1);
		}
		while(l<q[i].l){
			add(a[l],-1);
			cur-=sum(a[l]-1);
			l++;
		}
		while(r>q[i].r){
			add(a[r],-1);
			cur-=sum(n)-sum(a[r]);
			r--;
		}
		ans[q[i].id]=cur;
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}