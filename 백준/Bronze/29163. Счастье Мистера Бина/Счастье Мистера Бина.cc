#include <bits/stdc++.h>
using namespace std;
main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n; cin>>n;
    int even=0,odd=0;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        if(x%2==0) even++;
        else odd++;
    }
    cout<<(even>odd?"Happy":"Sad");
}