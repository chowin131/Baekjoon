#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> G(n+1);
    vector<bool> visited(n+1,0);
    queue<int> q;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    q.push(1);
    int count=-1;
    while(!q.empty()){
        int u=q.front();q.pop();
        if(visited[u]) continue;
        visited[u]=1;
        count++;
        for(int v:G[u])q.push(v);
    }
    cout<<count;
}