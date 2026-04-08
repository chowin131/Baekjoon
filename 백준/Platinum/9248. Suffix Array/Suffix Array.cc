#include <bits/stdc++.h>
using namespace std;
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    string s;
    cin>>s;
    int n=s.size();
    vector<int> sa(n),r(n),tmp(n);
    for(int i=0;i<n;i++) sa[i]=i, r[i]=s[i];
    for(int k=1;;k*=2){
        auto cmp=[&](int a,int b){
            if(r[a]!=r[b]) return r[a]<r[b];
            int ra=(a+k<n)?r[a+k]:-1;
            int rb=(b+k<n)?r[b+k]:-1;
            return ra<rb;
        };
        sort(sa.begin(),sa.end(),cmp);
        tmp[sa[0]]=0;
        for(int i=1;i<n;i++)
            tmp[sa[i]]=tmp[sa[i-1]]+(cmp(sa[i-1],sa[i])?1:0);
        for(int i=0;i<n;i++) r[i]=tmp[i];
        if(r[sa[n-1]]==n-1) break;
    }
    vector<int> rk(n),lcp(n,0);
    for(int i=0;i<n;i++) rk[sa[i]]=i;
    int h=0;
    for(int i=0;i<n;i++){
        if(rk[i]==0){ h=0; continue; }
        int j=sa[rk[i]-1];
        while(i+h<n&&j+h<n&&s[i+h]==s[j+h]) h++;
        lcp[rk[i]]=h;
        if(h) h--;
    }
    for(int i=0;i<n;i++) cout<<sa[i]+1<<" ";
    cout<<"\nx ";
    for(int i=1;i<n;i++) cout<<lcp[i]<<" ";
}