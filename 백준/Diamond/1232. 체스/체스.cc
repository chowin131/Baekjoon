#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
int d[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
const int MASK=(1<<21)-1;
int ht[6][1<<21];
int get_idx(int key){
    int h=key;
    h^=h>>21;
    h^=h>>17;
    h*=0x9E3779B97F4A7C15;
    h^=h>>29;
    return h&MASK;
}
int enc(int qx,int qy,int k1x,int k1y,int k2x,int k2y){
    if(k1x>k2x||(k1x==k2x&&k1y>k2y)){
        swap(k1x,k2x);
        swap(k1y,k2y);
    }
    int res=qx;
    res=(res<<7)|qy;
    res=(res<<7)|k1x;
    res=(res<<7)|k1y;
    res=(res<<7)|k2x;
    res=(res<<7)|k2y;
    return res;
}
int look(int dep,int key){
    if(dep>=6) return -1;
    int idx=get_idx(key);
    int entry=ht[dep][idx];
    if((entry&0xFFFFFFFFFFF)==key){
        int val=(entry>>60)&3;
        if(val==1) return 1;
        if(val==2) return 0;
    }
    return -1;
}
void store(int dep,int key,bool res){
    if(dep>=6) return;
    int idx=get_idx(key);
    int val=res?1:2;
    ht[dep][idx]=(val<<60)|key;
}
bool cap(int qx,int qy,int kx,int ky,int bx,int by){
    int dx=kx-qx,dy=ky-qy;
    if(dx==0&&dy==0) return false;
    if(dx!=0&&dy!=0&&abs(dx)!=abs(dy)) return false;
    int stepx=(dx==0)?0:(dx>0?1:-1);
    int stepy=(dy==0)?0:(dy>0?1:-1);
    int cx=qx+stepx,cy=qy+stepy;
    while(cx!=kx||cy!=ky){
        if(cx==bx&&cy==by) return false;
        cx+=stepx; cy+=stepy;
    }
    return true;
}
bool dfs(int qx,int qy,int k1x,int k1y,int k2x,int k2y,int dep){
    if(cap(qx,qy,k1x,k1y,k2x,k2y)||cap(qx,qy,k2x,k2y,k1x,k1y)) return true;
    if(dep==1) return false;
    int key=enc(qx,qy,k1x,k1y,k2x,k2y);
    int cached=look(dep,key);
    if(cached!=-1) return cached;
    for(int i=0;i<8;++i){
        int cx=qx+d[i][0],cy=qy+d[i][1];
        while(cx>=0&&cx<100&&cy>=0&&cy<100){
            if((cx==k1x&&cy==k1y)||(cx==k2x&&cy==k2y)) break;
            bool b_lose=true,b_has_moves=false;
            for(int j=0;j<8;++j){
                int nk1x=k1x+d[j][0],nk1y=k1y+d[j][1];
                if(nk1x>=0&&nk1x<100&&nk1y>=0&&nk1y<100)
                    if((nk1x!=cx||nk1y!=cy)&&(nk1x!=k2x||nk1y!=k2y)){
                        b_has_moves=true;
                        if(!dfs(cx,cy,nk1x,nk1y,k2x,k2y,dep-1)){
                            b_lose=false;
                            break;
                        }
                    }
            }
            if(b_lose)
                for(int j=0;j<8;++j){
                    int nk2x=k2x+d[j][0],nk2y=k2y+d[j][1];
                    if(nk2x>=0&&nk2x<100&&nk2y>=0&&nk2y<100)
                        if((nk2x!=cx||nk2y!=cy)&&(nk2x!=k1x||nk2y!=k1y)){
                            b_has_moves=true;
                            if(!dfs(cx,cy,k1x,k1y,nk2x,nk2y,dep-1)){
                                b_lose=false;
                                break;
                            }
                        }
                }
            if(!b_has_moves||b_lose){
                store(dep,key,true);
                return true;
            }
            cx+=d[i][0]; cy+=d[i][1];
        }
    }
    store(dep,key,false);
    return false;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int qx,qy,k1x,k1y,k2x,k2y;
    cin>>qx>>qy>>k1x>>k1y>>k2x>>k2y;
    for(int i=1;i<10;i++){
        if(dfs(qx,qy,k1x,k1y,k2x,k2y,i)){
            cout<<i;
            break;
        }
    }
}