#import<iostream>
using namespace std;
main(){
int n;
cin>>n;
if(n<2)cout<<"11\nA B C D E F G H J L M";
if(n>1&&n<4)cout<<"9\nA C E F G H I L M";
if(n==4)cout<<"9\nA B C E F G H L M";
if(n>4&&n<10)cout<<"8\nA C E F G H L M";
if(n==10)cout<<"8\nA B C F G H L M";
}