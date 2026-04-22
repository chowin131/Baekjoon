#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define f first
#define s second
using p=pair<int,int>;

const int MAX=100005;
const int SQ=700;
int a[MAX];
int bit[150][10005];
int bsz[150];
int n,m;

void add(int b,int idx,int val){
	for(int i=idx;i<=10000;i+=i&-i)bit[b][i]+=val;
}

int query(int b,int idx){
	int sum=0;
	for(int i=idx;i>0;i-=i&-i)sum+=bit[b][i];
	return sum;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		int b=i/SQ;
		add(b,a[i],1);
		bsz[b]++;
	}
	
	cin>>m;
	while(m--){
		int op;
		cin>>op;
		if(op==1){
			int i,v;
			cin>>i>>v;
			int b=i/SQ;
			add(b,a[i],-1);
			a[i]=v;
			add(b,a[i],1);
		}else{
			int l,r,k;
			cin>>l>>r>>k;
			
			if(k>=10000){
				cout<<0<<"\n";
				continue;
			}
			
			int b_l=l/SQ,b_r=r/SQ;
			int ans=0;
			
			if(b_l==b_r){
				for(int i=l;i<=r;i++)if(a[i]>k)ans++;
			}
			else{
				for(int i=l;i<(b_l+1)*SQ;i++){
					if(a[i]>k)ans++;
				}
				for(int b=b_l+1;b<b_r;b++)ans+=bsz[b]-query(b,k);
				
				for(int i=b_r*SQ;i<=r;i++)if(a[i]>k)ans++;
			}
			cout<<ans<<"\n";
		}
	}
	return 0;
}