#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p = pair<int,int>;
#define f first
#define s second
struct Node{
    int l,r,p,sz,val,flip,l1,r1,m1;
} t[100010];
int a[100010];
int root;
void apply(int x){
    if(!x)return;
    swap(t[x].l,t[x].r);
    swap(t[x].l1,t[x].r1);
    t[x].flip^=1;
}
void push(int x){
    if(t[x].flip){
        apply(t[x].l);
        apply(t[x].r);
        t[x].flip=0;
    }
}
void update(int x){
    if(!x)return;
    int l=t[x].l,r=t[x].r;
    t[x].sz=1;
    if(l)t[x].sz+=t[l].sz;
    if(r)t[x].sz+=t[r].sz;
    t[x].l1=l?t[l].l1:0;
    if((!l||t[l].l1==t[l].sz)&&t[x].val)t[x].l1+=1+(r?t[r].l1:0);
    t[x].r1=r?t[r].r1:0;
    if((!r||t[r].r1==t[r].sz)&&t[x].val)t[x].r1+=1+(l?t[l].r1:0);
    t[x].m1=t[x].val;
    if(l)t[x].m1=max(t[x].m1,t[l].m1);
    if(r)t[x].m1=max(t[x].m1,t[r].m1);
    if(t[x].val)t[x].m1=max(t[x].m1,(l?t[l].r1:0)+1+(r?t[r].l1:0));
}
void rotate(int x){
    int p=t[x].p,b=0;
    if(x==t[p].l){
        t[p].l=b=t[x].r;
        t[x].r=p;
    }else{
        t[p].r=b=t[x].l;
        t[x].l=p;
    }
    t[x].p=t[p].p;
    t[p].p=x;
    if(b)t[b].p=p;
    if(t[x].p){
        if(p==t[t[x].p].l)t[t[x].p].l=x;
        else t[t[x].p].r=x;
    }
    update(p);update(x);
}
void splay(int x,int g=0){
    while(t[x].p!=g){
        int p=t[x].p,pp=t[p].p;
        if(pp!=g){
            if((x==t[p].l)==(p==t[pp].l))rotate(p);
            else rotate(x);
        }
        rotate(x);
    }
    if(!g)root=x;
}
void find_kth(int k,int g=0){
    int x=root;
    push(x);
    while(1){
        int l=t[x].l,lsz=l?t[l].sz:0;
        if(k==lsz+1)break;
        if(k<=lsz)x=l;
        else{
            k-=lsz+1;
            x=t[x].r;
        }
        push(x);
    }
    splay(x,g);
}
void gather(int l,int r){
    find_kth(l);
    find_kth(r+2,root);
}
int build(int l,int r,int p){
    if(l>r)return 0;
    int mid=(l+r)/2;
    int x=mid;
    t[x].p=p;
    t[x].val=a[x];
    t[x].flip=0;
    t[x].l=build(l,mid-1,x);
    t[x].r=build(mid+1,r,x);
    update(x);
    return x;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    for(int i=2;i<=n+1;++i)cin>>a[i];
    a[1]=0;
    a[n+2]=0;
    root=build(1,n+2,0);
    int m;
    cin>>m;
    while(m--){
        int op,l,r;cin>>op>>l>>r;
        if(op==1){
            gather(l,r);
            int x=t[t[root].r].l;
            apply(x);
            update(t[root].r);
            update(root);
        }
        else{
            gather(l,r);
            cout<<t[t[t[root].r].l].m1<<"\n";
        }
    }
}