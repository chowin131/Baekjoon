#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define int long long

int to_num(char c){
    if(c<='9'&&c>='0') return c-'0';
    return c-'A'+10;
}
char to_char(int x){
    if(x<10) return '0'+x;
    return 'A'+x-10;
}
bool cmp(vector<int>&a,vector<int>&b){
    for(int i=(int)a.size()-1;i>=0;i--){
        if(a[i]!=b[i]) return a[i]>b[i];
    }
    return false;
}
void carry(vector<int>&a){
    for(int i=0;i+1<(int)a.size();i++){
        a[i+1]+=a[i]/36;
        a[i]%=36;
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,k;
    string input[50];
    cin>>n;
    for(int i=0;i<n;i++) cin>>input[i];
    cin>>k;
    int max_len=0;
    for(int i=0;i<n;i++) max_len=max(max_len,(int)input[i].length());
    vector<vector<int>> v(36,vector<int>(max_len+2));
    vector<int> result(max_len+2);
    vector<bool> used(36);

    for(int i=0;i<n;i++){
        int len=input[i].length();
        for(int j=0;j<len;j++){
            int num=to_num(input[i][len-1-j]);
            result[j]+=num;
            v[num][j]+=35-num;
        }
    }

    carry(result);
    for(int i=0;i<36;i++) carry(v[i]);

    for(int t=0;t<k;t++){
        int idx=-1;
        for(int i=0;i<36;i++){
            if(used[i]) continue;
            if(idx==-1||cmp(v[i],v[idx])) idx=i;
        }
        if(idx==-1) break;
        used[idx]=1;
        for(int i=0;i<max_len+2;i++) result[i]+=v[idx][i];
        carry(result);
    }

    int idx=max_len+1;
    while(idx>0&&result[idx]==0) idx--;
    for(int i=idx;i>=0;i--) cout<<to_char(result[i]);
}