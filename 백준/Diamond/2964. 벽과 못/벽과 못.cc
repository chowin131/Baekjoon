#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
int ccw(p a,p b,p c){
    int res=(b.f-a.f)*(c.s-a.s)-(b.s-a.s)*(c.f-a.f);
    if(res>0)return 1;
    if(res<0)return -1;
    return 0;
}
int area_sum(p a,p b){
    return a.f*b.s-b.f*a.s;
}
set<p> UH,LH;
int S_UH=0,S_LH=0;
void add_UH(p P){
    auto it=UH.lower_bound(P);
    if(it!=UH.begin()&&it!=UH.end()){
        auto L=prev(it),R=it;
        if(ccw(*L,P,*R)>=0)return;
    }
    it=UH.insert(P).first;
    if(it!=UH.begin()&&next(it)!=UH.end())S_UH-=area_sum(*prev(it),*next(it));
    if(it!=UH.begin())S_UH+=area_sum(*prev(it),P);
    if(next(it)!=UH.end())S_UH+=area_sum(P,*next(it));
    while(it!=UH.begin()){
        auto L1=prev(it);
        if(L1==UH.begin())break;
        auto L2=prev(L1);
        if(ccw(*L2,*L1,P)>=0){
            S_UH-=area_sum(*L2,*L1);
            S_UH-=area_sum(*L1,P);
            S_UH+=area_sum(*L2,P);
            UH.erase(L1);
        }
        else break;
    }
    while(true){
        auto R1=next(it);
        if(R1==UH.end())break;
        auto R2=next(R1);
        if(R2==UH.end())break;
        if(ccw(P,*R1,*R2)>=0){
            S_UH-=area_sum(P,*R1);
            S_UH-=area_sum(*R1,*R2);
            S_UH+=area_sum(P,*R2);
            UH.erase(R1);
        }else break;
    }
}
void add_LH(p P){
    auto it=LH.lower_bound(P);
    if(it!=LH.begin()&&it!=LH.end()){
        auto L=prev(it),R=it;
        if(ccw(*L,P,*R)<=0)return;
    }
    it=LH.insert(P).first;
    if(it!=LH.begin()&&next(it)!=LH.end())S_LH-=area_sum(*prev(it),*next(it));
    if(it!=LH.begin())S_LH+=area_sum(*prev(it),P);
    if(next(it)!=LH.end())S_LH+=area_sum(P,*next(it));
    while(it!=LH.begin()){
        auto L1=prev(it);
        if(L1==LH.begin())break;
        auto L2=prev(L1);
        if(ccw(*L2,*L1,P)<=0){
            S_LH-=area_sum(*L2,*L1);
            S_LH-=area_sum(*L1,P);
            S_LH+=area_sum(*L2,P);
            LH.erase(L1);
        }else break;
    }
    while(true){
        auto R1=next(it);
        if(R1==LH.end())break;
        auto R2=next(R1);
        if(R2==LH.end())break;
        if(ccw(P,*R1,*R2)<=0){
            S_LH-=area_sum(P,*R1);
            S_LH-=area_sum(*R1,*R2);
            S_LH+=area_sum(P,*R2);
            LH.erase(R1);
        }
        else break;
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin>>N;
    vector<pair<p,int>> pts(N);
    for(int i=0;i<N;++i){
        cin>>pts[i].f.f>>pts[i].f.s;
        pts[i].s=i;
    }
    string q_str;
    cin>>q_str;
    vector<pair<p,int>> px=pts;
    vector<pair<p,int>> py=pts;
    sort(px.begin(),px.end(),[](auto& a,auto& b){return a.f.f<b.f.f;});
    sort(py.begin(),py.end(),[](auto& a,auto& b){return a.f.s<b.f.s;});
    int lx=0,rx=N-1,dy=0,uy=N-1;
    vector<bool> rm(N,false);
    vector<p> rm_pts;
    for(char q:q_str){
        int id=-1;
        if(q=='L'){
            while(rm[px[lx].s])lx++;
            id=px[lx].s;
        }
        else if(q=='R'){
            while(rm[px[rx].s])rx--;
            id=px[rx].s;
        }
        else if(q=='U'){
            while(rm[py[uy].s])uy--;
            id=py[uy].s;
        }
        else if(q=='D'){
            while(rm[py[dy].s])dy++;
            id=py[dy].s;
        }
        rm[id]=true;
        rm_pts.push_back(pts[id].f);
    }
    vector<p> rem;
    for(int i=0;i<N;++i)if(!rm[i])rem.push_back(pts[i].f);
    p pt1=rem[0],pt2=rem[1];
    if(pt1.f>pt2.f)swap(pt1,pt2);
    UH.insert(pt1);
    UH.insert(pt2);
    LH.insert(pt1);
    LH.insert(pt2);
    S_UH=area_sum(pt1,pt2);
    S_LH=area_sum(pt1,pt2);
    vector<int> ans;
    reverse(rm_pts.begin(),rm_pts.end());
    for(auto P:rm_pts){
        add_UH(P);
        add_LH(P);
        int diff=S_LH-S_UH;
        if(diff<0)diff=-diff;
        ans.push_back(diff);
    }
    reverse(ans.begin(),ans.end());
    for(auto v:ans)cout<<v/2<<"."<<(v%2==0?0:5)<<"\n";
}