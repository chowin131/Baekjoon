#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Node {
    int val,sum,lazy;
    int32_t l,r,sz;
    uint32_t pri;
};
Node nodes[8000005];
int32_t node_cnt=0;
int32_t root=0;
mt19937 rng(1337);
int32_t clone(int32_t p){
    if(!p)return 0;
    int32_t q=++node_cnt;
    nodes[q]=nodes[p];
    return q;
}
void update(int32_t p){
    if(!p)return;
    nodes[p].sz=1;
    nodes[p].sum=nodes[p].val;
    if(nodes[p].l){
        nodes[p].sz+=nodes[nodes[p].l].sz;
        nodes[p].sum+=nodes[nodes[p].l].sum;
    }
    if(nodes[p].r){
        nodes[p].sz+=nodes[nodes[p].r].sz;
        nodes[p].sum+=nodes[nodes[p].r].sum;
    }
}
void push_down(int32_t p){
    if(nodes[p].lazy){
        if(nodes[p].l){
            nodes[p].l=clone(nodes[p].l);
            nodes[nodes[p].l].val+=nodes[p].lazy;
            nodes[nodes[p].l].sum+=nodes[p].lazy*nodes[nodes[p].l].sz;
            nodes[nodes[p].l].lazy+=nodes[p].lazy;
        }
        if(nodes[p].r){
            nodes[p].r=clone(nodes[p].r);
            nodes[nodes[p].r].val+=nodes[p].lazy;
            nodes[nodes[p].r].sum+=nodes[p].lazy*nodes[nodes[p].r].sz;
            nodes[nodes[p].r].lazy+=nodes[p].lazy;
        }
        nodes[p].lazy=0;
    }
}
void split(int32_t p,int32_t k,int32_t &l,int32_t &r){
    if(!p){
        l=r=0;
        return;
    }
    p=clone(p);
    push_down(p);
    int32_t left_sz=nodes[p].l?nodes[nodes[p].l].sz:0;
    if(left_sz>=k){
        split(nodes[p].l,k,l,nodes[p].l);
        r=p;
    }else{
        split(nodes[p].r,k-left_sz-1,nodes[p].r,r);
        l=p;
    }
    update(p);
}
int32_t merge(int32_t l,int32_t r){
    if(!l||!r)return l?l:r;
    if(nodes[l].pri>nodes[r].pri){
        int32_t p=clone(l);
        push_down(p);
        nodes[p].r=merge(nodes[p].r,r);
        update(p);
        return p;
    }else{
        int32_t p=clone(r);
        push_down(p);
        nodes[p].l=merge(l,nodes[p].l);
        update(p);
        return p;
    }
}
int n,m;
int A[200005];
int acnt=0;
void inorder(int32_t p){
    if(!p)return;
    push_down(p);
    inorder(nodes[p].l);
    A[++acnt]=nodes[p].val;
    inorder(nodes[p].r);
}
int32_t st[200005];
void rebuild(){
    acnt=0;
    inorder(root);
    node_cnt=0;
    int32_t top=0;
    for(int i=1;i<=n;++i){
        int32_t p=++node_cnt;
        nodes[p].val=A[i];
        nodes[p].lazy=0;
        nodes[p].pri=rng();
        nodes[p].l=nodes[p].r=0;
        int32_t last=0;
        while(top>0&&nodes[st[top]].pri<nodes[p].pri){
            last=st[top];
            top--;
        }
        nodes[p].l=last;
        if(top>0)nodes[st[top]].r=p;
        st[++top]=p;
    }
    root=st[1];
    auto update_all=[&](auto self,int32_t p)->void{
        if(!p)return;
        self(self,nodes[p].l);
        self(self,nodes[p].r);
        update(p);
    };
    update_all(update_all,root);
}
void check_gc(){
    if(node_cnt>7500000)rebuild();
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>A[i];
    rebuild();
    cin>>m;
    while(m--){
        int type;cin>>type;
        if(type==1){
            int L,R,X;cin>>L>>R>>X;
            int32_t L1,R1,T_mid;
            split(root,L-1,L1,R1);
            split(R1,R-L+1,T_mid,R1);
            T_mid=clone(T_mid);
            nodes[T_mid].val+=X;
            nodes[T_mid].sum+=X*nodes[T_mid].sz;
            nodes[T_mid].lazy+=X;
            root=merge(merge(L1,T_mid),R1);
        }
        else if(type==2){
            int L,R,S,E;cin>>L>>R>>S>>E;
            int32_t L1,R1,T_copy;
            split(root,S-1,L1,R1);
            split(R1,E-S+1,T_copy,R1);
            root=merge(merge(L1,T_copy),R1);
            int32_t L2,R2,T_del;
            split(root,L-1,L2,R2);
            split(R2,R-L+1,T_del,R2);
            root=merge(merge(L2,T_copy),R2);
        }else if(type==3){
            int L,R;cin>>L>>R;
            int32_t L1,R1,T_mid;
            split(root,L-1,L1,R1);
            split(R1,R-L+1,T_mid,R1);
            cout<<nodes[T_mid].sum<<'\n';
            root=merge(merge(L1,T_mid),R1);
        }
        check_gc();
    }
    return 0;
}