#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define int long long
main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int q,m;
    cin>>q>>m;
    int pre=0,cur=1;
    int T;
    for(int i=1;i<=m*m;i++){
        int next=(pre+cur)%m;
        if(cur==0&&next==1){
            T=i;
            break;
        }
        pre=cur;
        cur=next;
    }
    vector<int> v;
    pre=1,cur=1;
    v.push_back(1);
    for(int i=1;i<T;i++){
        string str=to_string(cur);
        for(char c:str) v.push_back(c-'0');
        int next=(pre+cur)%m;
        pre=cur;
        cur=next;
    }
    int new_T=v.size();
    while(q--){
        int n;
        cin>>n;
        n--;
        cout<<v[n%new_T]<<"\n";
    }
}