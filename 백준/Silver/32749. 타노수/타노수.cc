#include<iostream>
#include<string>
#include<string_view>
using namespace std;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int n,t;
	cin>>n>>t;
	string x;
	cin>>x;
	int s=1<<(n-t),b=1<<t;
	string_view m="",v(x);
	for(int i=0;i<b;++i){
		string_view c=v.substr(i*s,s);
		if(c>m)m=c;
	}
	cout<<m;
}