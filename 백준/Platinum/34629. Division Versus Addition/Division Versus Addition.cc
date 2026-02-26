#include<bits/stdc++.h>
using namespace std;
main(){
    cin.tie(0)->sync_with_stdio(0);
    int t,n,q,i,Log,r;
    for(cin>>t;t--;){
        cin>>n>>q;
        vector<int>v(n),N=v,L=v;
        for(int&j:v)cin>>j,j--;
        for(i=0;i<n;i++){
            Log=log2(v[i]);
            Log+=(Log==0||Log!=log2(v[i]));
            L[i]=(1<<Log==v[i])+(i>0?L[i-1]:0);
            N[i]=Log+(i>0?N[i-1]:0);
        }
        for(i=0;i<q;i++){
            cin>>Log>>r;
            cout<<N[r-1]-(Log>1?N[Log-2]:0)+(L[r-1]-(Log>1?L[Log-2]:0))/2<<"\n";
        }
    }
}