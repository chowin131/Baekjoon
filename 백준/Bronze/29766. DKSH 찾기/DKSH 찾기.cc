#include <bits/stdc++.h>
using namespace std;
vector<int> func(const string& p){
    int m=p.size();
    vector<int> v(m,0);
    for(int i=1,j=0;i<m;i++){
        while(j>0&&p[i]!=p[j]) j=v[j-1];
        if(p[i]==p[j]) v[i]=++j;
    }
    return v;
}
main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    string t;
    cin>>t;
    string p="DKSH";
    auto v=func(p);
    int cnt=0,m=p.size();
    for(int i=0,j=0;i<(int)t.size();i++){
        while(j>0&&t[i]!=p[j]) j=v[j-1];
        if(t[i]==p[j]) j++;
        if(j==m) cnt++,j=v[j-1];
    }
    cout<<cnt<<"\n";
}