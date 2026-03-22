#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int p,m;
        cin>>p>>m;
        int result=2;
        int temp1=1,temp2=1;
        while(result++){
            int cur=(temp1+temp2)%m;
            int next=(cur+temp2)%m;
            if(cur==0&&next==1) break;
            temp1=temp2;
            temp2=cur;
        }
        cout<<p<<" "<<result<<"\n";
    }
}