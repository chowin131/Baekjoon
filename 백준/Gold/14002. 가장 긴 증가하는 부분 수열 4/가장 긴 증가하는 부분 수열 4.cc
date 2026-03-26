#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
int main(){
    int n,M=0,M_idx=0;
    cin>>n;
    vector<int> input(n);
    vector<pair<int,int>> in(n);
    for(int i=0;i<n;i++) cin>>input[i];
    in[0]={0,-1};
    for(int i=1;i<n;i++){
        in[i]={0,-1};
        for(int j=0;j<i;j++){
            if(input[j]<input[i]){
                if(in[j].first+1>in[i].first){
                    in[i]={in[j].first+1,j};
                }
            }
        }
        if(M<in[i].first){
            M=in[i].first;
            M_idx=i;
        }
    }
    cout<<M+1<<'\n';
    vector<int> result;
    result.push_back(input[M_idx]);
    int idx=in[M_idx].second;
    while(result.size()<M+1){
        result.push_back(input[idx]);
        idx=in[idx].second;
    }
    for(int i=M;i>=0;i--) cout<<result[i]<<' ';
}