#include<bits/stdc++.h>
using namespace std;
vector<int> v(26);
int main(){
    string s;
    cin>>s;
    for(char i:s){
        v[i-'a']++;
    }
    cout<<v[0]+v['e'-'a']+v['i'-'a']+v['o'-'a']+v['u'-'a'];
}