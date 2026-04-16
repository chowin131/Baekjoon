#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    vector<int> g(max(n-1,2),0);
    auto mex=[&](set<int>& s){
        int m=0;
        while(s.count(m)) m++;
        return m;
    };
    for(int k=2;k<g.size();k++){
        set<int> s;
        for(int a=0;a<=k-2;a++) s.insert(g[a]^g[k-2-a]);
        g[k]=mex(s);
    }
    set<int> s;
    for(int a=0;a<=n-2;a++)
        s.insert(g[a]^g[n-2-a]);
    cout<<(mex(s)?1:2);
}