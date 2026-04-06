#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n,k;
    cin>>n>>k;
    queue<pair<int,int>> q;
    vector<vector<int>> visited(500001,vector<int>(2,-1));
    q.push({n,0});
    visited[n][0]=0;
    while(!q.empty()){
        int cur=q.front().first;
        int time=q.front().second;
        q.pop();
        for(int next:{cur+1,cur-1,cur*2}){
            if(next<0||next>500000) continue;
            if(visited[next][!(time%2)]==-1){
                q.push({next,time+1});
                visited[next][!(time%2)]=time+1;
            }
        }
    }
    int ans=1000000;
    for(int t=0;k<=500000;k+=++t){
        if(visited[k][t%2]!=-1&&visited[k][t%2]<=t)
            ans=min(ans,t);
    }
    if(ans!=1000000) cout<<ans;
    else cout<<-1;
}