#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<int,int>>> G(100000);
pair<int,int> dfs(int cur,int par,int tar_cost,int cost){
    int temp=cost;
    for(auto next:G[cur]){
        if(next.first==par) continue;
        auto [f,s]=dfs(next.first,cur,tar_cost,temp+next.second);
        if(s!=-1) return {f,s};
        cost=max(cost,f);
    }
    if(cost==tar_cost) return {cost,cur};
    return {cost,-1};
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int u,v,c;
        cin>>u>>v;
        while(v!=-1){
            cin>>c;
            G[u-1].push_back({v-1,c});
            cin>>v;
        }
        // for(auto j:G[i])cout<<j.first<<" "<<j.second<<" ";
        // cout<<"\n";
    }
    cout<<dfs(dfs(0,-1,dfs(0,-1,-1,0).first,0).second,-1,-1,0).first;
}