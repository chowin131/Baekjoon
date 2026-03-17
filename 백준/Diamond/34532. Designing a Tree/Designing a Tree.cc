#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int base=1,n;
    cin>>n;
    while(base<n) base*=2;
    vector<vector<int>> seg(2*base);//세그 트리를 선언해줍니다
    //base 값을 설정함으로써 완전이진트리로 구성했습니다
    //각 노드가 배열을 하나씩 갖고, 그 배열에는 문제가 제시한 것처럼 자신의 부모 후보들이 저장될 것입니다

    for(int i=0;i<n-1;i++){//구간 범위에 부모 후보들을 저장하는 과정입니다!
        int s,e;
        cin>>s>>e;
        s+=base-1,e+=base-1;//s, e를 리프 노드의 인덱스로 조정해줍니다(입력은 1 - based 인덱스여서 -1이 더 붙어야 합니다!)
        while(s<=e){
            if(s&1) seg[s].push_back(i),s++;//&(and) 연산을 사용했는데 비트연산이기 때문에 홀수인지 짝수인지 판별해준다고 보시면 될 것 같습니다
            if(!(e&1)) seg[e].push_back(i),e--;//그냥 %보다 빨라서 사용했어요
            s/=2,e/=2;//더 빠른 최적화를 원하신다면 <<를 사용하시고, e--같은 후위 연산자보다 전위 연산자를 사용해주는 것이 좋습니다
            /*
                좀 더 자세히 알아보니 내장 타입(int 등)에서는 결과를 사용하지 않으면 보통 차이 거의 없다고 합니다.
                원래 후위 연산자를 사용하면 기존 값을 저장해놓고, 참조 형식으로 해당 변수의 값을 증가 시킨 다음에 기존 값을 return하는데
                결과를 사용하지 않으면 기존 값을 return할 필요가 없기 때문에 컴파일러에서 기계어 번역 과정에서 거의 동일하게 취급한다고 하네요:)
            */
        }
    }
    queue<int> q;
    vector<bool> visited(n);
    vector<int> result(n-1);//결과 저장하는 배열입니다! 트리 상으로 자신의 부모를 저장한다고 생각하시면 될 것 같습니다.
    q.push(n-1);
    visited[n-1]=1;
    /*
    여기서 굉장히 중요한 포인트가 있는데 바로 n-1 노드를 queue에 넣고 방문처리 한다는 점입니다!!
    n-1 노드를 넣은 이유는 바로 n-1 노드는 자신의 자식이 없기 때문이죠!!!
    무방향 간선이라서 부모-자식 관계가 있냐고 하실 수도 있겠지만 
    문제 조건을 잘 보시면 [각 i(1≤i≤N-1)번 정점에 대해 L_i≤j_i≤R_i(1≤L_i≤R_i≤N)인 j_i를 골라서 i번 정점과 j_i번 정점을 연결하는 무향 간선을 추가할 수 있다.]라고 했죠
    즉 N번 노드에 대한 정보는 주어지지 않았기 때문에 N번 노드가 목적지 같는 개념으로 사용될 수 있는거죠
    그래서 N번 노드부터 역순으로 탐색해줄 생각입니다!
    */
    while(!q.empty()){
        int cur=q.front();
        cur+=base;//넣을 때 0-based로 넣어줘서 base만 더해줍니다
        //바로 pop을 안해준 이유는 cur이 중간에 연산에 참가할껀데 front 값이 한 번 더 사용될 예정이라 그렇습니다
        vector<int> next;//다음으로 방문할 후보군 배열
        while(cur>0){
            if(!seg[cur].empty()){
                next.insert(next.end(),seg[cur].begin(),seg[cur].end());
                //문법에 관해서 간단히 설명하자면 "next 벡터의 end, 즉 마지막 요소 다음 칸에 seg[cur]의 시작부터 끝까지 집어넣겠다"라는 의미입니다.
                seg[cur].clear();//사용했으니 지워주기~
            }
            cur>>=1;//부모노드로 올라가는 트릭이죠
        }
        for(int N:next){
            if(visited[N]) continue;//방문한 적 있으면 절대 가면 안됩니다!! (회로가 만들어져요!)
            q.push(N);
            visited[N]=1;//방문처리하고
            result[N]=(q.front()+1);//result도 업데이트
        }
        q.pop();
    }
    for(bool i:visited){//한 노드라도 방문한 적이 없다면? -> 전체를 트리로 못만든다는 말!
        if(!i){
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES\n";//그게 아니면 성공, 출력하기
    for(int i:result){
        cout<<i<<' ';
    }
}