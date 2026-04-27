#include <bits/stdc++.h>
using namespace std;
using p=pair<int,int>;
#define f first
#define s second
int ev_hd[1000005],ev_cnt[1000005];
int ev_dt[6500005],ev_cur[1000005];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,t;
    cin>>n>>t;
    int sx,sy;
    cin>>sx>>sy;
    sx--,sy--;
    bitset<1024> base;
    bitset<1024> k_msk[905];
    map<int,int> mp;
    int m=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int k;
            cin>>k;
            if(k==1) base.set(i*32+j);
            else if(k<=t){
                if(mp.find(k)==mp.end()) mp[k]=m++;
                k_msk[mp[k]].set(i*32+j);
            }
        }
    }
    for(auto& x:mp){
        int k=x.f;
        for(int i=k;i<=t;i+=k)ev_cnt[i]++;
    }
    ev_hd[0]=0;
    for(int i=1;i<=t;i++){
        ev_hd[i]=ev_hd[i-1]+ev_cnt[i-1];
        ev_cur[i]=ev_hd[i];
    }
    for(auto& x:mp){
        int k=x.f,idx=x.s;
        for(int i=k;i<=t;i+=k)ev_dt[ev_cur[i]++]=idx;
    }
    bitset<1024> v;
    v.set(sx*32+sy);
    for(int i=1;i<=t;i++){
        bitset<1024> val=base;
        for(int j=ev_hd[i];j<ev_cur[i];j++)val|=k_msk[ev_dt[j]];
        v=((v<<65)|(v<<63)|(v>>63)|(v>>65)|(v<<34)|(v<<30)|(v>>30)|(v>>34))&val;
        if(v.none())break;
    }
    vector<p> ans;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(v.test(i*32+j))ans.push_back({i+1,j+1});
        }
    }
    cout<<ans.size()<<"\n";
    for(auto& x:ans)cout<<x.f<<" "<<x.s<<"\n";
}