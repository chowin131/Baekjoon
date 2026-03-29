#include<iostream>
int n,s,x;
main(){
std::cin>>n;
while(std::cin>>x)s+=x;
std::cout<<(s<0?"Left":(s?"Right":"Stay"));
}