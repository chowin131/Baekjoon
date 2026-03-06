#include<bits/stdc++.h>
using namespace std;
#define I long
#define f first
#define s second
#define P pair<I,I>
I ccw(P a,P b,P c){return(b.f-a.f)*(c.s-a.s)-(b.s-a.s)*(c.f-a.f);}
main(){
cin.tie(0)->sync_with_stdio(0);
I n,r,i;
cin>>n;
vector<P> p(n),C;
for(auto&i:p)cin>>i.f>>i.s;
sort(p.begin(),p.end());
for(i=0;i<n;i++){
while(C.size()>1&&ccw(C[C.size()-2],C.back(),p[i])<0)C.pop_back();
C.push_back(p[i]);
}
r=C.size();
C.clear();
for(i=n-1;i>=0;i--){
while(C.size()>1&&ccw(C[C.size()-2],C.back(),p[i])<0)C.pop_back();
C.push_back(p[i]);
}
r+=C.size();
cout<<3*n-r-1;
}