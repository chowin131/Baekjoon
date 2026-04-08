#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long
vector<int> seg,lazy;//기본적으로 세그 배열이 있고, 레이지는 우리가 추가로 더할 것들을 따로 저장해놓은 배열
int n,m,k,base=1;//n은 총 크기, m이랑 k는 쿼리 개수, base는 세그 트리를 포화 이진트리로 만들기 위한 상수값
void push(int node,int s,int e){//현재 노드에 해당하는 레이지!! 값을 자식들로 전파하고 자신은 0이 됨.
    if(lazy[node]!=0){
        seg[node]+=(e-s+1)*lazy[node];//자신의 값을 seg에 업데이트
        if(s!=e){
            lazy[node*2]+=lazy[node];//왼쪽 자식으로 전파
            lazy[node*2+1]+=lazy[node];//오른쪽 자식으로 전파
        }
        lazy[node]=0;//자기 자신은 초기화(전파 다했으니 쓸모 없어져서)
    }
}
void update(int node,int s,int e,int l,int r,int val){//쿼리 중에 업데이트에 해당하는 쿼리 구현임.
    push(node,s,e);//일단 자기 위치 부분의 레이지 값을 초기화하고 자식으로 전파했다 생각
    if(r<s||e<l)return;//재귀의 base case, 끝나는 지점
    if(l<=s&&e<=r){//완전 포함될 경우
        lazy[node]+=val;
        push(node,s,e);
        return;
    }
    int mid=(s+e)/2;//완전 포함되는게 아니면 재귀로 접근
    update(node*2,s,mid,l,r,val);//왼쪽
    update(node*2+1,mid+1,e,l,r,val);//오른쪽
    seg[node]=seg[node*2]+seg[node*2+1];//재귀 끝났으니깐 업데이트
}
int ssum(int node,int s,int e,int l,int r){//값을 구할꺼임!!
    push(node,s,e);//레이지 초기화 및 자식으로 전파(seg 값에 레이지가 잘 반영되어야 해서 꼭 필수!!)
    if(r<s||e<l)return 0;//이것도 베이스 케이스, 끝나는 지점
    if(l<=s&&e<=r)return seg[node];//완전 포함되면 이것도 베이스 케이스
    int mid=(s+e)/2;
    return ssum(node*2,s,mid,l,r)+ssum(node*2+1,mid+1,e,l,r);//재귀로 접근 왼쪽+오른쪽
}
main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    while(base<n)base*=2;//포화 이진트리로 만들기 위한 상수 계산
    seg.resize(base*2);
    lazy.resize(base*2);
    for(int i=base;i<base+n;i++)cin>>seg[i];//입력
    for(int i=base-1;i>0;i--)seg[i]=seg[i*2]+seg[i*2+1];//초기화, 원래 했던 방식이라 이해하기 쉬울꺼임
    for(int i=0;i<m+k;i++){
        int a,b,c,d;
        cin>>a>>b>>c;
        if(a==1){//업데이트 쿼리
            cin>>d;
            update(1,1,base,b,c,d);
        }
        else if(a==2){//출력 쿼리(ssum 호출로 값 계산할꺼임)
            cout<<ssum(1,1,base,b,c)<<'\n';
        }
    }
    return 0;
}