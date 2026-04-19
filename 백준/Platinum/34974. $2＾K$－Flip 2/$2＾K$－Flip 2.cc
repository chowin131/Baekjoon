#include<iostream>
using namespace std;
using U=unsigned long long;
long long P[65],S;
U M[65];
int A[65],N,K,l,r;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>N>>K;
	P[0]=1;
	for(int i=1;i<=64;++i)P[i]=P[i-1]*2%998244353;
	for(int i=0;i<N;++i)cin>>A[i];
	for(int i=0;i<K;++i){
		cin>>l>>r;
		for(int j=l-1;j<r;++j)M[j]|=1ULL<<i;
	}
	for(int i=0;i<N;++i){
		U B[64]={0};
		int T[64]={0},k=0;
		bool o=1;
		for(int j=i;j<N;++j){
			U m=M[j];
			int t=!A[j];
			for(int b=63;b>=0;--b){
				if((m>>b)&1){
					if(!B[b]){B[b]=m;T[b]=t;k++;m=0;t=0;break;}
					m^=B[b];t^=T[b];
				}
			}
			if(!m&&t)o=0;
			if(!o)break;
			S=(S+P[K-k])%998244353;
		}
	}
	cout<<S;
}