#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int a,b;
    cin>>a>>b;
    //2~100만 사이의 제곱 수를 구함 -> 다 소수의 제곱이 될 것 -> 8만개 언더
	//100만개의 수들이 각각 8만개의 소수로 나눠떨어지는지/안나눠떨어지는지 체크하는거, 근데 그냥 해도 시간 안터질듯
	vector<int> p,visited(1000000);
	p.reserve(1000000);
	p.push_back(4);
	for(int i=3;i<=1000000;i+=2){
		if(visited[i]) continue;
		p.push_back(i*i);
		for(int j=i;j<=1000000;j+=2*i){
			visited[j]=1;
		}
	}
	vector<int> result(b-a+1);
	for(int i=0;i<p.size();i++){
		int tar=((a+p[i]-1)/p[i])*p[i];
		while(tar<=b){
			result[tar-a]=1;
			tar+=p[i];
		}
	}
	int cnt=0;
	for(int i:result)if(i==0)cnt++;
	cout<<cnt;
}