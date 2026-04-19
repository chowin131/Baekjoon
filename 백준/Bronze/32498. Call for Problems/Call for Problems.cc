#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,d,c=0;
    cin>>n;
    while(n--) cin>>d, c+=d%2;
    cout<<c;
}
