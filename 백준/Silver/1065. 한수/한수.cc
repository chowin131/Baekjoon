#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    int cnt=0;
    for(int i=1;i<=n;++i){
        if(i<100)cnt++;
        else if(i<1000){
            int a=i/100,b=(i/10)%10,c=i%10;
            if(a-b==b-c)cnt++;
        }
    }
    cout<<cnt<<"\n";
}