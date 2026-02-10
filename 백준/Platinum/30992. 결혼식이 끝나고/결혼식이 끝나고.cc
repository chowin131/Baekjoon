#include <bits/stdc++.h>
#define int long long
using namespace std;
const int P=998244353;
int pw(int a,int b){
    int r=1;
    a%=P;
    if(a<0) a+=P;
    for(;b;b>>=1){
        if(b&1) r=r*a%P;
        a=a*a%P;
    }
    return r;
}
int inv(int a){return pw(a,P-2);}
int M(int a){return((a%P)+P)%P;}
signed main(){
    int n;
    cin>>n;
    vector<int> x(n),y(n);
    for(int&i:x)cin>>i;
    for(int&i:y)cin>>i;
    int s2=0,s4=0;
    int i3=inv(3),i5=inv(5);
    for(int i=0;i<n-1;i++){
        int d=M(x[i+1]-x[i]);
        int a=M(y[i]),dy=M(y[i+1]-y[i]);
        int a2=a*a%P,a3=a2*a%P,a4=a3*a%P;
        int dy2=dy*dy%P,dy3=dy2*dy%P,dy4=dy3*dy%P;
        s2=(s2+d*(a2+a*dy%P+dy2*i3%P)%P)%P;
        s4=(s4+d*(a4+2*a3%P*dy%P+2*a2%P*dy2%P+a*dy3%P+dy4*i5%P)%P)%P;
    }
    cout<<M(s4)*inv(M(s2))%P;
}