#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<vector<int>> T(n+1);
    int root=1;
    for (int i=0;i<n-1;i++) {
        int a,b;
        cin>>a>>b;
        T[a].push_back(b);
        T[b].push_back(a);
    }
    vector<int> par(n+1,0);
    par[root]=root;
    queue<int> q;
    q.push(root);
    vector<vector<int>> new_T(22001);
    while (!q.empty()) {
        int cur=q.front();
        q.pop();
        for (int next:T[cur]) {
            if (par[next]==0) {
                q.push(next);
                par[next]=cur;
            }
        }
    }
    int val=n;
    q.push(root);
    while (!q.empty()) {
        int tar=q.front();
        q.pop();
        vector<int> child;
        for (int nb:T[tar]) if (nb!=par[tar]) child.push_back(nb);
        if (child.size()==0) continue;
        else if (child.size()==1) {
            int prev=tar;
            for (int i=0;i<10;i++) {
                new_T[prev].push_back(++val);
                prev=val;
            }
            new_T[prev].push_back(child[0]);
            q.push(child[0]);
        }
        else {
            int k=child.size();
            int h=0;
            while ((1<<h)<k) h++;
            int pad=10-h;
            int prev=tar;
            for (int i=0;i<pad;i++) {
                new_T[prev].push_back(++val);
                prev=val;
            }
            int R=prev;
            int sz=1<<(h+1);
            vector<int> nd(sz);
            nd[1]=R;
            for (int i=2;i<sz;i++) nd[i]=++val;
            for (int i=1;i<(1<<h);i++) {
                new_T[nd[i]].push_back(nd[2*i]);
                new_T[nd[i]].push_back(nd[2*i+1]);
            }
            int s=1<<h;
            for (int i=0;i<k;i++) {
                new_T[nd[s+i]].push_back(child[i]);
                q.push(child[i]);
            }
        }
    }
    cout<<val<<"\n";
    for (int i=1;i<=val;i++) {
        for (int j:new_T[i]) {
            cout<<i<<" "<<j<<"\n";
        }
    }
}