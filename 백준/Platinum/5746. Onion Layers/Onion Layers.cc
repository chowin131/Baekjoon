#include<bits/stdc++.h>
using namespace std;
struct pt{ int x,y,id; };
int ccw(pt a,pt b,pt c){ return (((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x))<0); }
main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
int n;
while(cin>>n&&n){
vector<pt> P(n);
for(int i=0;i<n;i++){
cin>>P[i].x>>P[i].y;
P[i].id=i;
}
sort(P.begin(),P.end(),[&](pt a,pt b){
if(a.x==b.x) return a.y<b.y;
return a.x<b.x;
});
vector<int> mark(n,0);
int cnt=1;
while(P.size()>=3){
int m=P.size();
vector<pt> L,U,N;
N.reserve(m),L.reserve(m),U.reserve(m);
for(auto i:P){
while(L.size()>1&&ccw(L[L.size()-2],L.back(),i)) L.pop_back();
L.push_back(i);
}
for(int i=m-1;i>=0;i--){
while(U.size()>1&&ccw(U[U.size()-2],U.back(),P[i])) U.pop_back();
U.push_back(P[i]);
}
for(auto i:L) mark[i.id]=cnt;
for(auto i:U) mark[i.id]=cnt;
for(auto p:P) if(mark[p.id]!=cnt) N.push_back(p);
P.swap(N);
cnt++;
}
if(cnt&1) cout<<"Do not take this onion to the lab!\n";
else cout<<"Take this onion to the lab!\n";
}
}