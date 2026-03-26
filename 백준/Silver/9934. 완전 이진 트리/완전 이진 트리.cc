#include <iostream>
#include <vector>
using namespace std;
int n;
vector<int> v;
vector<vector<int>> result;
void fill(int l,int r,int depth){
    if(l>r) return;
    int m=(l+r)/2;
    result[depth].push_back(v[m]);
    if(depth==n) return;
    fill(l,m-1,depth+1);
    fill(m+1,r,depth+1);
}
int main(){
    cin>>n;
    v.resize((1<<n)-1);
    result.resize(n);
    for(int&i:v)cin>>i;
    fill(0,v.size()-1,0);
    for(int i=0;i<n;i++){
        for(int j:result[i])cout<<j<<" ";
        cout<<"\n";
    }
}