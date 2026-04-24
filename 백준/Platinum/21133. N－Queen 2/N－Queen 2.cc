#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p = pair<int,int>;
#define f first
#define s second
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> e,o;
    for(int i=2;i<=n;i+=2)e.push_back(i);
    for(int i=1;i<=n;i+=2)o.push_back(i);
    if(n%6==2){
        swap(o[0],o[1]);
        o.erase(find(o.begin(),o.end(),5));
        o.push_back(5);
    }
    else if(n%6==3){
        e.erase(e.begin());
        e.push_back(2);
        o.erase(o.begin());
        o.erase(o.begin());
        o.push_back(1);
        o.push_back(3);
    }
    for(int x:e)cout<<x<<"\n";
    for(int x:o)cout<<x<<"\n";
}