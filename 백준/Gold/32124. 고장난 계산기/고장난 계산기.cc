#include<bits/stdc++.h>
using namespace std;
string ans;
bool is_d(char c){
    return '0'<=c&&c<='9';
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n>>m>>ans;
    for(int i=0;i<(int)ans.length();i++){
        if(ans[i]=='*'){
            int left=i-1,right=i+1;
            if(left>=0&&is_d(ans[left])){
                while(left>=0&&is_d(ans[left])) left--;
                left++;
            }
            else if(left>=0&&ans[left]==')'){
                int cnt=1;
                while(cnt){
                    left--;
                    if(ans[left]==')') cnt++;
                    else if(ans[left]=='(') cnt--;
                }
            }
            if(right<(int)ans.size()&&is_d(ans[right])){
                while(right<(int)ans.size()&&is_d(ans[right])) right++;
                right--;
            }
            else if(right<(int)ans.size()&&ans[right]=='('){
                int cnt=1;
                while(cnt){
                    right++;
                    if(ans[right]=='(') cnt++;
                    else if(ans[right]==')') cnt--;
                }
            }
            string temp=ans.substr(0,left)+"("+ans.substr(left,right-left+1)+")"+ans.substr(right+1);
            ans=temp;
            i++;
        }
    }
    cout<<ans.length()<<"\n"<<ans;
}