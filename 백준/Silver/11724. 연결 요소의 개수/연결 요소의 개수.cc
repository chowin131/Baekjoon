#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    vector<vector<int>> G(n);
    vector<bool> visited(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int cnt=0;
    for(int i=0;i<n;i++){
        if(visited[i]) continue;
        visited[i]=1;
        cnt++;
        queue<int> q;
        q.push(i);
        while(!q.empty()){
            int cur=q.front();
            q.pop();
            for(int next:G[cur]){
                if(visited[next]) continue;
                visited[next]=1;
                q.push(next);
            }
        }
    }
    cout<<cnt;
}