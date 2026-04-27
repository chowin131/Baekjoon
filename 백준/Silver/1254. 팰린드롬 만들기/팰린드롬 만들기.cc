#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    string str;
    cin>>str;
    int n=str.size();
    for(int i=0;i<n;++i){
        bool flag=1;
        for(int j=0;j<(n-i)/2;++j)
            if(str[i+j]!=str[n-1-j]){
                flag=0;
                break;
            }
        if(flag){
            cout<<n+i;
            return 0;
        }
    }
}