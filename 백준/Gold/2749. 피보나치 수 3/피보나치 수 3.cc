#include <iostream>
using namespace std;
long long arr[2000001];
int main() {
    arr[0] = 0;
    arr[1] = 1;
    long long N;
    cin>>N;
    N%=1500000;
    for(int i=2;i<=N;i++)
        arr[i]=(arr[i-1]+arr[i-2])%1000000;
    cout<<arr[N];
}