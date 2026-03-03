#include <bits/stdc++.h>
using namespace std;
int len;
string str;
vector<int> N;
vector<char> O;
int cal(int a, char op, int b){
    if(op=='+') return a+b;
    if(op=='-') return a-b;
    return a*b;
}
int solve(int mask){
    int m=O.size();
    int prev=-2;
    for(int i=0;i<m;i++){
        if(mask&(1<<i)){
            if(i==prev+1) return INT32_MIN;
            prev=i;
        }
    }
    vector<int> v=N;
    vector<char> o=O;
    for(int i=m-1;i>=0;i--){
        if(mask&(1<<i)){
            int val=cal(v[i],o[i],v[i+1]);
            v[i]=val;
            v.erase(v.begin()+i+1);
            o.erase(o.begin()+i);
        }
    }
    int result=v[0];
    for(int i=0;i<o.size();i++) result=cal(result,o[i],v[i+1]);
    return result;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>len>>str;
    for(int i=0;i<len;i++){
        if(i%2==0) N.push_back(str[i]-'0');
        else O.push_back(str[i]);
    }
    if(len==1){
        cout<<str[0];
        return 0;
    }
    int m=O.size();
    int result=INT32_MIN;
    for(int i=0;i<(1<<m);i++){
        int val=solve(i);
        if(val!=INT32_MIN) result=max(result,val);
    }
    cout<<result;
}