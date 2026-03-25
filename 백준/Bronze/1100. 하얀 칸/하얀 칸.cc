#include<iostream>
#include<string>
using namespace std;

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int ans=0;
    string row;
    for(int i=0;i<8;i++){
        cin>>row;
        for(int j=0;j<8;j++) if((i+j)%2==0&&row[j]=='F') ans++;
    }
    cout<<ans;
    return 0;
}