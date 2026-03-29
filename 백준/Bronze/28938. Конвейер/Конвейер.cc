#include<iostream>
int s,x;
main(){
std::cin>>x;
while(std::cin>>x)s+=x;
std::cout<<(s<0?"Left":s?"Right":"Stay");
}