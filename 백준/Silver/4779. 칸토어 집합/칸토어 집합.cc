#include <iostream>
#include <vector>
using namespace std;
void fill(vector<bool>&target,int center,int len){
    if(len==1) return;
    if(len==3) target[center]=0;
    else{
        for(int i=center-len/6;i<=center+len/6;i++) target[i]=0;
        fill(target,center-len/2+len/6,len/3);
        fill(target,center+len/2-len/6,len/3);
    }
}
int main(){
    int n;
    while(cin>>n){
        int m=1;
        for(int i=0;i<n;i++) m*=3;
        vector<bool> result(m,1);
        fill(result,m/2,m);
        for(bool i:result) cout<<(i?'-':' ');
        cout<<'\n';
    }
}