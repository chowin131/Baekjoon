#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> v(n),result(n,-1);
    stack<int> s;
    for(int i=0;i<n;i++){
        cin>>v[i];
        while(!s.empty()&&v[s.top()]<v[i]){
            result[s.top()]=v[i];
            s.pop();
        }
        s.push(i);
    }
    for(int i:result) cout<<i<<" ";
}