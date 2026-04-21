#include<iostream>
using namespace std;int c=-2,v,i;string s;int main(){cin>>s;if(s=="1")return cout<<1,0;for(i=s.size();i--;s[i]=(v+10)%10+48)v=(s[i]-48)*2+c,c=v<0?-1:v/10;if(c>0)cout<<c;cout<<s;}