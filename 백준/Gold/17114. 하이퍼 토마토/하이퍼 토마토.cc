#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int D[11],S[11],N=1;
    for(int i=0;i<11;i++){
        cin>>D[i];
        S[i]=N;
        N*=D[i];
    }
    vector<int> a(N);
    queue<int> q;
    int cnt=0;
    for(int i=0;i<N;i++){
        cin>>a[i];
        if(a[i]==1)q.push(i);
        if(a[i]==0)cnt++;
    }
    int ans=1;
    while(q.size()){
        int idx=q.front();
        q.pop();
        for(int k=0;k<11;k++){
            int c=(idx/S[k])%D[k];
            if(c>0){
                int nx=idx-S[k];
                if(a[nx]==0){
                    a[nx]=a[idx]+1;
                    cnt--;
                    ans=max(ans,a[nx]);
                    q.push(nx);
                }
            }
            if(c<D[k]-1){
                int nx=idx+S[k];
                if(a[nx]==0){
                    a[nx]=a[idx]+1;
                    cnt--;
                    ans=max(ans,a[nx]);
                    q.push(nx);
                }
            }
        }
    }
    cout<<(cnt?-1:ans-1);
}