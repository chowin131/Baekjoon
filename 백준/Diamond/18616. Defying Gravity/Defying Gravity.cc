#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    map<p,int> mp;
    int nxt=1;
    int L=129600;
    vector<int> a(L,0);
    for(int i=0;i<n;++i){
        int r,ph,m;
        cin>>r>>ph>>m;
        if(!mp.count({r,m}))mp[{r,m}]=nxt++;
        a[ph]=mp[{r,m}];
    }
    vector<int> S(3*L);
    for(int i=0;i<3*L;++i)S[i]=a[i%L];
    vector<int> t(6*L+3);
    t[0]=-1;
    t[1]=0;
    for(int i=0;i<3*L;++i){
        t[2*i+2]=S[i];
        t[2*i+3]=0;
    }
    t[6*L+2]=-2;

    vector<int> P(6*L+3,0);
    int C=0,R=0;
    for(int i=1;i<6*L+2;++i){
        int im=2*C-i;
        if(R>i)P[i]=min(R-i,P[im]);
        else P[i]=0;
        while(t[i+1+P[i]]==t[i-1-P[i]])P[i]++;
        if(i+P[i]>R){
            C=i;
            R=i+P[i];
        }
    }
    vector<double> ans;
    for(int i=2*L+2;i<=4*L+1;++i)
        if(P[i]>=L){
            int num=i-2*L-2;
            double al=num/2.0;
            if(num%2==0&&a[num/2]!=0)continue;
            ans.push_back(al);
        }
    cout<<ans.size()<<"\n";
    cout<<fixed<<setprecision(7);
    for(double x:ans)cout<<x<<"\n";
}