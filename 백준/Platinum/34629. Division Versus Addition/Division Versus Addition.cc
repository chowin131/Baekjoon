#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,q;
        cin>>n>>q;
        vector<int> v(n);
        for(int&i:v)cin>>i,i--;
        vector<int> need(n),line(n);
        for(int i=0;i<n;i++){
            int Log=log2(v[i]);
            if(Log==0||Log!=log2(v[i])) Log++;
            line[i]=(i>0?line[i-1]:0);
            if((1<<Log)==v[i]) line[i]++;
            need[i]=Log+(i>0?need[i-1]:0);
        }
        for(int i=0;i<q;i++){
            int l,r;
            cin>>l>>r;
            l--,r--;
            cout<<need[r]-(l>0?need[l-1]:0)+(line[r]-(l>0?line[l-1]:0))/2<<"\n";
        }
    }
}