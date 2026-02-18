#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int n;
vector<int> a,t;
ll func(int l,int r){
    if(l==r) return 0;
    int m=(l+r)/2;
    ll cnt=func(l,m)+func(m+1,r);
    int i=l,j=m+1,k=l;
    while(i<=m&&j<=r){
        if(a[i]<=a[j]) t[k++]=a[i++];
        else t[k++]=a[j++],cnt+=m-i+1;
    }
    while(i<=m) t[k++]=a[i++];
    while(j<=r) t[k++]=a[j++];
    for(int x=l;x<=r;x++) a[x]=t[x];
    return cnt;
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    a.resize(n),t.resize(n);
    for(int i=0;i<n;i++) cin>>a[i];
    cout<<func(0,n-1);
}
