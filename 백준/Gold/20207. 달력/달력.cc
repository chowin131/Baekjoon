#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> v(367);
    for (int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        v[a]++,v[b+1]--;
    }
    int result=0,temp=0,h=0;
    for (int i=1;i<=366;i++) v[i]+=v[i-1];
    for (int i=1;i<=365;i++){
        if (v[i]==0) h=0;
        else if (v[i]>h){
            if (h==0) temp=i;
            h=v[i];
        }
        if (v[i]!=0&&v[i+1]==0){
            result+=(i-temp+1)*h;
        }
    }
    cout<<result;
}