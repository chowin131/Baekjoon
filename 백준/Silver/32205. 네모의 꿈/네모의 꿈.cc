#include<bits/stdc++.h>
using namespace std;
int n,i,v;
main(){
ios::sync_with_stdio(0);
unordered_set<int>s;
for(cin>>n;i++<3*n;)cin>>v,s.insert(v);
cout<<(s.size()!=3*n);
}