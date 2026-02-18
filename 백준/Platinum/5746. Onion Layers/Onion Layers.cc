#include <bits/stdc++.h>
using namespace std;
struct pt{
    int x,y,id;
};
int ccw(pt a,pt b,pt c){
    return (((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x))<0);
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n;
    while(cin>>n){
        if(n==0) break;
        vector<pt> P(n);
        for(int i=0;i<n;i++){
            cin>>P[i].x>>P[i].y;
            P[i].id=i;
        }
        sort(P.begin(),P.end(),[&](pt a,pt b){
            if(a.x==b.x) return a.y<b.y;
            return a.x<b.x;
        });
        vector<int> mark(n,0);
        int cnt=1;
        while(P.size()>=3){
            int m=P.size();
            vector<pt> lower,upper;
            for(int i=0;i<m;i++){
                while(lower.size()>=2&&ccw(lower[lower.size()-2],lower.back(),P[i])) lower.pop_back();
                lower.push_back(P[i]);
            }
            for(int i=m-1;i>=0;i--){
                while(upper.size()>=2&&ccw(upper[upper.size()-2],upper.back(),P[i])) upper.pop_back();
                upper.push_back(P[i]);
            }
            for(int i=0;i<lower.size();i++) mark[lower[i].id]=cnt;
            for(int i=0;i<upper.size();i++) mark[upper[i].id]=cnt;
            vector<pt> nxt;
            nxt.reserve(P.size());
            for(auto &p:P) if(mark[p.id]!=cnt) nxt.push_back(p);
            P.swap(nxt);
            cnt++;
        }
        if(cnt&1) cout<<"Do not take this onion to the lab!\n";
        else cout<<"Take this onion to the lab!\n";
    }
} 