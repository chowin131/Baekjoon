#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int cal(int x,char c,int y){
	if(c=='+') return x+y;
	if(c=='-') return x-y;
	return x*y;
}
int solve(int i,int cur){
	int ans=INT32_MIN;
	if(i>=n) return cur;
	ans=max(ans,solve(i+2,cal(cur,s[i-1],s[i]-'0')));
	if(i<n-2) ans=max(ans,solve(i+4,cal(cur,s[i-1],cal(s[i]-'0',s[i+1],s[i+2]-'0'))));
	return ans;
}
int main(){
	cin>>n>>s;
	cout<<solve(2,s[0]-'0');
}