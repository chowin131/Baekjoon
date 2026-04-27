#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p = pair<int,int>;
#define f first
#define s second
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    string k,st;
    int n;
    cin>>k>>st>>n;
    int kx=k[0]-'A',ky=k[1]-'1';
    int sx=st[0]-'A',sy=st[1]-'1';
    auto in=[&](int x,int y){
        return x>=0&&x<8&&y>=0&&y<8;
    };
    while(n--){
        string op;
        cin>>op;
        int dx=0,dy=0;
        for(char c:op){
            if(c=='R')dx++;
            if(c=='L')dx--;
            if(c=='T')dy++;
            if(c=='B')dy--;
        }
        int nkx=kx+dx,nky=ky+dy;
        if(!in(nkx,nky))continue;
        if(nkx==sx&&nky==sy){
            int nsx=sx+dx,nsy=sy+dy;
            if(!in(nsx,nsy))continue;
            sx=nsx;sy=nsy;
        }
        kx=nkx;ky=nky;
    }
    cout<<(char)(kx+'A')<<(char)(ky+'1')<<"\n";
    cout<<(char)(sx+'A')<<(char)(sy+'1');
}