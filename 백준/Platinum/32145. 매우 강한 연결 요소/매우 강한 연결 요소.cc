#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define P pair<int,int>
int ccw(P a,P b,P c){return(b.f-a.f)*(c.s-a.s)-(b.s-a.s)*(c.f-a.f);}
main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,r;
    cin>>n;
    vector<P> pt(n),C;
    for(auto&i:pt)cin>>i.f>>i.s;
    sort(pt.begin(),pt.end(),[](P a,P b){
        if(a.f==b.f)return a.s<b.s;
        return a.f<b.f;
    });
    for(int i=0;i<n;i++){
        while(C.size()>1&&ccw(C[C.size()-2],C.back(),pt[i])<0)C.pop_back();
        C.push_back(pt[i]);
    }
    r=C.size();
    C.clear();
    for(int i=n-1;i>=0;i--){
        while(C.size()>1&&ccw(C[C.size()-2],C.back(),pt[i])<0)C.pop_back();
        C.push_back(pt[i]);
    }
    r+=C.size()-2;
    cout<<3*n-r-3;
}