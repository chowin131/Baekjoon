#include<bits/stdc++.h>
using namespace std;
#define int long long
const int M=998244353;
int pw(int a,int b){
	int r=1;
	for(;b;b>>=1,a=a*a%M)if(b&1)r=r*a%M;
	return r;
}
int N,cnt[26][26],out[26],inS[26],ed[200005];
int A[52][53],B[26][27],C[26][27];
void slv(int n,auto&A){
	for(int i=0;i<n;++i){
		int p=i;
		for(int j=i;j<n;++j)if(A[j][i]){p=j;break;}
		for(int k=0;k<=n;++k)swap(A[i][k],A[p][k]);
		int iv=pw(A[i][i],M-2);
		for(int k=i;k<=n;++k)A[i][k]=A[i][k]*iv%M;
		for(int j=0;j<n;++j)if(i!=j&&A[j][i]){
			int f=A[j][i];
			for(int k=i;k<=n;++k)A[j][k]=(A[j][k]-f*A[i][k]%M+M)%M;
		}
	}
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>N;
	for(int i=0;i<N;++i){
		string s;
        cin>>s;
		int u=s[0]-'A',v=s.back()-'A';
		cnt[u][v]++;out[u]++;ed[i]=v;
	}
	queue<int>q;
	for(int i=0;i<26;++i)if(!out[i]){inS[i]=1;q.push(i);}
	while(q.size()){
		int v=q.front();q.pop();
		for(int u=0;u<26;++u)
            if(cnt[u][v]&&!inS[u]){inS[u]=1;q.push(u);}
	}
	for(int i=0;i<26;++i){
		if(!out[i]){
			A[i][i]=1;A[26+i][26+i]=1;A[26+i][52]=1;
			B[i][i]=1;C[i][i]=1;
		}
        else if(!inS[i]){
			A[i][i]=1;A[26+i][26+i]=1;
			B[i][i]=1;B[i][26]=1;C[i][i]=1;
		}
        else{
			A[i][i]=out[i];A[26+i][26+i]=out[i];
			for(int j=0;j<26;++j){
				int v=(M-cnt[i][j]%M)%M;
				A[i][26+j]=v;
				A[26+i][j]=v;
				B[i][j]=v;
				C[i][j]=v;
			}
			B[i][i]=(B[i][i]+out[i])%M;
			C[i][i]=(C[i][i]+out[i])%M;
			C[i][26]=out[i]%M;
		}
	}
	slv(52,A);
    slv(26,B);
    slv(26,C);
	for(int i=0;i<N;++i){
		int v=ed[i];
		cout<<A[26+v][52]<<" "<<A[v][52]<<" "<<B[v][26]<<" "<<(C[v][26]+1)%M<<"\n";
	}
}