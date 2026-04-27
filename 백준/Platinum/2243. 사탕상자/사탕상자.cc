#include <bits/stdc++.h>
using namespace std;
int t[4000001];
void u(int n,int s,int e,int idx,int v){
    if(idx<s||idx>e)return;
    t[n]+=v;
    if(s!=e){
        int m=(s+e)/2;
        u(n*2,s,m,idx,v);
        u(n*2+1,m+1,e,idx,v);
    }
}
int q(int n,int s,int e,int k){
    if(s==e)return s;
    int m=(s+e)/2;
    if(t[n*2]>=k)return q(n*2,s,m,k);
    else return q(n*2+1,m+1,e,k-t[n*2]);
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    while(n--){
        int a;
        cin>>a;
        if(a==1){
            int b;
            cin>>b;
            int res=q(1,1,1000000,b);
            cout<<res<<"\n";
            u(1,1,1000000,res,-1);
        }
        else{
            int b,c;
            cin>>b>>c;
            u(1,1,1000000,b,c);
        }
    }
}