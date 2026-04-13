#include <bits/stdc++.h>
using namespace std;
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,h;
    cin>>n>>h;
    vector<int> v(h+1);
    for (int i=0;i<n;i++){
        int val;
        cin>>val;
        if (i%2==0){
            v[0]++;
            v[val]--;
        }
        else{
            v[h]--;
            v[h-val]++;
        }
    }
    int result=INT32_MAX,cnt=0;
    for (int i=1;i<=h;i++) v[i]+=v[i-1];
    for (int i=0;i<h;i++){
        if (v[i]<result){
            result=v[i];
            cnt=0;
        }
        if (v[i]==result) cnt++;
    }
    cout<<result<<" "<<cnt;
}