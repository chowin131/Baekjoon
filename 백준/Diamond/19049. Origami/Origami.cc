#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int S(vector<string>&v){
int k=v[0].size();
if(k==1) return 1LL;
vector<int> R(k,1e9);
string t;
t.reserve(2*k+1);
vector<int> rad(2*k+1);
for(auto& x:v){
t="#";
for(char ch:x) t+=ch,t+="#";
int len=t.size(),c=0,r=0;
for(int i=0;i<len;i++){
rad[i]=0;
if(i<r) rad[i]=min(r-i,rad[2*c-i]);
while(i-rad[i]-1>=0&&i+rad[i]+1<len&&t[i-rad[i]-1]==t[i+rad[i]+1]) rad[i]++;
if(i+rad[i]>r) c=i,r=i+rad[i];
}
for(int i=1;i<k;i++) R[i]=min(R[i],rad[2*i]/2);
}
vector<bool> c_L(k+1,false),c_R(k+1,false);
c_L[1]=c_R[k]=true;
int mx_L=1,mn_R=k;
for(int i=1;i<k;i++) if(mx_L>=i-R[i]+1) c_L[i+1]=true,mx_L=max(mx_L,i+1);
for(int i=k-1;i>=1;i--) if(mn_R<=i+R[i]) c_R[i]=true,mn_R=min(mn_R,i);
vector<int> sf_R(k+2,0);
for(int i=k;i>=1;i--) sf_R[i]=sf_R[i+1]+c_R[i];
int cnt=0;
for(int i=1;i<=k;i++) if(c_L[i]) cnt+=sf_R[i];
return cnt;
}
main(){
cin.tie(0)->sync_with_stdio(0);
cin>>n>>m;
vector<string> a(n),b(m,string(n,' '));
for(auto&i:a) cin>>i;
for(int i=0;i<n;i++) for(int j=0;j<m;j++) b[j][i]=a[i][j];
cout<<S(a)*S(b);
}