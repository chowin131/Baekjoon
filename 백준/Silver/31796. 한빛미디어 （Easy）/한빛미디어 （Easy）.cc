#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int n,i;
	cin>>n;
	vector<int> s(n);
	for(i=0;i<n;i++)cin>>s[i];
	sort(s.begin(),s.end());
	int p=0;
    i=0;
	while(i<n){
		p++;
		int m=s[i];
		while(i<n&&s[i]<m*2)i++;
	}
	cout<<p;
}