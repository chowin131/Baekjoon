#include <iostream>
#include <vector>
using namespace std;
#define int long long
main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> v(n);
    for(int&i:v) cin>>i;
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        int o;
        cin>>o;
        if(o==1){
            int c,x;
            cin>>c>>x;
            c--;
            int temp=x;
            for(int j=c;j>=0&&temp;j--){
                if(v[j]>=temp){
                    v[j]+=temp;
                    break;
                }
                temp-=v[j];
                v[j]*=2;
            }
            temp=x;
            for(int j=c+1;j<n;j++){
                if(v[j]>=temp){
                    v[j]+=temp;
                    break;
                }
                temp-=v[j];
                v[j]*=2;
            }
        }   
        else if(o==2){
            int c;
            cin>>c;
            c--;
            cout<<v[c]<<'\n';
        }
    }
}