#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin>>s;
    crope r(s.c_str());
    int q;
    cin>>q;
    while(q--){
        int t,x;
        cin>>t>>x;
        if(t==1){
            int y;
            cin>>y;
            crope sub=r.substr(x,y-x+1);
            r.erase(x,y-x+1);
            r.insert(0,sub);
        }
        else if(t==2){
            int y;
            cin>>y;
            crope sub=r.substr(x,y-x+1);
            r.erase(x,y-x+1);
            r+=sub;
        }
        else cout<<r[x]<<'\n';
    }
}