#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin>>q;
    priority_queue<int> l;
    priority_queue<int,vector<int>,greater<int>> r;
    int m=0;
    while(q--){
        int t;
        cin>>t;
        if(t==1){
            int x,y;
            cin>>x>>y;
            if(l.empty()){
                l.push(x);
                r.push(x);
                m+=y;
            }
            else{
                m+=y;
                if(x<l.top()){
                    l.push(x);
                    l.push(x);
                    m+=l.top()-x;
                    r.push(l.top());
                    l.pop();
                }
                else{
                    r.push(x);
                    r.push(x);
                    m+=x-r.top();
                    l.push(r.top());
                    r.pop();
                }
            }
        }
        else cout<<l.top()<<" "<<m<<"\n";
    }
}