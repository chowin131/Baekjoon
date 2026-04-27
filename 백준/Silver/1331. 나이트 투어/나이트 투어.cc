#include <bits/stdc++.h>
using namespace std;
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    string s;
    int v[6][6]={0};
    int sx,sy,cx,cy;
    int flag=1;
    for(int i=0;i<36;++i){
        cin>>s;
        int nx=s[0]-'A',ny=s[1]-'1';
        if(!i)sx=nx,sy=ny;
        else{
            if(v[nx][ny])flag=0;
            int dx=abs(cx-nx),dy=abs(cy-ny);
            if(!((dx==1&&dy==2)||(dx==2&&dy==1)))flag=0;
        }
        v[nx][ny]=1;
        cx=nx;cy=ny;
    }
    int dx=abs(cx-sx),dy=abs(cy-sy);
    if(!((dx==1&&dy==2)||(dx==2&&dy==1)))flag=0;
    cout<<(flag?"Valid":"Invalid");
}