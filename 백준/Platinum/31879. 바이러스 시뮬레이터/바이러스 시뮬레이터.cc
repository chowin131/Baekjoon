#include <bits/stdc++.h>
using namespace std;

vector<pair<long long,int>> seg;
int n,base=1;
struct Gold{ 
    long long total,msum,lsum,rsum; 
    bool all_pos;
};
vector<Gold> gold_seg;
vector<long long> arr;

void update(int idx){
    idx+=base;
    for(idx/=2;idx>0;idx/=2){
        if(seg[idx*2].first>=seg[idx*2+1].first) seg[idx]=seg[idx*2];
        else seg[idx]=seg[idx*2+1];
    }
}

Gold merge(Gold&l,Gold&r){
    Gold ret;
    ret.total=l.total+r.total;
    ret.all_pos=(l.all_pos&&r.all_pos);
    if(l.all_pos) ret.lsum=l.total+r.lsum;
    else ret.lsum=l.lsum;
    if(r.all_pos) ret.rsum=r.total+l.rsum;
    else ret.rsum=r.rsum;
    
    ret.msum=max({l.msum,r.msum,l.rsum+r.lsum});
    return ret;
}

void update_gold(int idx){
    long long val=arr[idx];
    idx+=base;
    if(val>0) gold_seg[idx]={val,val,val,val,1};
    else gold_seg[idx]={0,0,0,0,0};
    for(idx/=2;idx;idx/=2){
        gold_seg[idx]=merge(gold_seg[idx*2],gold_seg[idx*2+1]);
    }
}

int find_max(int l,int r,int node,int cur_l,int cur_r){
    if(r<=cur_l||cur_r<=l) return -1;
    if(l<=cur_l&&cur_r<=r){
        if(seg[node].first==0) return -1;
        return seg[node].second;
    }
    int mid=(cur_l+cur_r)/2;
    int left=find_max(l,r,node*2,cur_l,mid),right=find_max(l,r,node*2+1,mid,cur_r);
    if(left==-1) return right;
    if(right==-1) return left;
    if(seg[base+left].first>=seg[base+right].first) return left;
    return right;
}

Gold query_gold(int l,int r,int node,int cur_l,int cur_r){
    if(r<=cur_l||cur_r<=l) return {0,0,0,0,0};
    if(l<=cur_l&&cur_r<=r) return gold_seg[node];
    
    int mid=(cur_l+cur_r)/2;
    Gold left=query_gold(l,r,node*2,cur_l,mid);
    Gold right=query_gold(l,r,node*2+1,mid,cur_r);
    return merge(left,right);
}

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int q;
    cin>>n>>q;
    while(base<n)base*=2;
    seg.resize(base*2);
    gold_seg.resize(base*2);
    arr.resize(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
        seg[base+i]={arr[i],i};
        if(arr[i]>0) gold_seg[base+i]={arr[i],arr[i],arr[i],arr[i],1};
        else gold_seg[base+i]={0,0,0,0,0};
    }
    for(int i=base-1;i>0;i--){
        if(seg[i*2].first>=seg[i*2+1].first) seg[i]=seg[i*2];
        else seg[i]=seg[i*2+1];
    }
    for(int i=base-1;i>0;i--){
        gold_seg[i]=merge(gold_seg[i*2],gold_seg[i*2+1]);
    }
    
    for(int i=0;i<q;i++){
        int o,tar;
        long long val;
        cin>>o>>tar>>val;
        tar--;
        if(o==1){
            while(val>0&&tar<n){
                if(arr[tar]>val){
                    arr[tar]-=val;
                    seg[base+tar].first-=val;
                    update(tar);
                    update_gold(tar);
                    break;
                }
                val-=arr[tar];
                arr[tar]=0;
                seg[base+tar].first=0;
                update(tar);
                update_gold(tar);
                
                int max_idx=find_max(tar+1,n,1,0,base);
                if(max_idx==-1) break;
                tar=max_idx;
            }
        }
        else if(o==2){
            arr[tar]+=val;
            seg[base+tar].first+=val;
            update(tar);
            update_gold(tar);
        }
        else{
            Gold result=query_gold(tar,val,1,0,base);
            cout<<result.msum<<'\n';
        }
    }
}