#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cout<<fixed;
    cout.precision(6);
    int n;
    cin>>n;
    vector<pair<int,int>> pt(n);
    vector<int> X(n);
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        pt[i]={a,b};
        X[i]=a;
    }
    sort(X.begin(),X.end());
    X.erase(unique(X.begin(),X.end()),X.end());
    int idx=X.size();
    vector<vector<int>> P(idx);
    for(int i=0;i<n;i++){
        int a=pt[i].first,b=pt[i].second;
        int xi=lower_bound(X.begin(),X.end(),a)-X.begin();
        P[xi].push_back(b);
    }
    for(int i=0;i<idx;i++){
        int mn=*min_element(P[i].begin(),P[i].end());
        int mx=*max_element(P[i].begin(),P[i].end());
        if(mn==mx) P[i]={mn};
        else P[i]={mn,mx};
    }
    vector<vector<double>> dp(idx);
    for(int i=0;i<idx;i++) dp[i].assign(P[i].size(),0);
    auto dist=[&](int x1,int y1,int x2,int y2)->double{
        double ax=X[x1],ay=P[x1][y1];
        double bx=X[x2],by=P[x2][y2];
        return sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay));
    };
    double result=0;
    for(int i=1;i<idx;i++){
        for(int j=0;j<(int)P[i].size();j++){
            for(int k=0;k<(int)P[i-1].size();k++){
                dp[i][j]=max(dp[i][j],dp[i-1][k]+dist(i-1,k,i,j));
                result=max(result,dp[i][j]);
            }
        }
    }
    cout<<result;
}