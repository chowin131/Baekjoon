#include <bits/stdc++.h>
using namespace std;
#define int long long

int memo[10][1<<10];
char board[10][10];

void dfs(vector<int>&cands,int cur,int idx,int m){
    if(idx==m){cands.push_back(cur);return;}
    dfs(cands,cur,idx+1,m);
    if(idx>0&&(cur>>(idx-1)&1))return;
    dfs(cands,cur|(1<<idx),idx+1,m);
}

int dp(vector<int>&cands,int row,int prev,int n,int m){
    if(row==n)return 0;
    if(memo[row][prev]!=-1)return memo[row][prev];
    int ans=0;
    for(int msk:cands){
        int bits=0,cnt=0;
        bool ok=true;
        for(int i=0;i<m;i++){
            if(!(msk>>i&1))continue;
            if(board[row][i]=='x'){ok=false;break;}
            if(i>0&&(prev>>(i-1)&1)){ok=false;break;}
            if(i<m-1&&(prev>>(i+1)&1)){ok=false;break;}
            bits|=(1<<i);
            cnt++;
        }
        if(!ok)continue;
        ans=max(ans,dp(cands,row+1,bits,n,m)+cnt);
    }
    return memo[row][prev]=ans;
}

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        memset(memo,-1,sizeof memo);
        int n,m;
        cin>>n>>m;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                cin>>board[i][j];
        vector<int>cands;
        dfs(cands,0,0,m);
        cout<<dp(cands,0,0,n,m)<<'\n';
    }
}