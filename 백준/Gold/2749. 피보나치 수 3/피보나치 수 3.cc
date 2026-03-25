#import<iostream>
long a[2000001]={0,1},n,i=1;main(){std::cin>>n,n%=1500000;for(;i++<n;)a[i]=(a[i-1]+a[i-2])%1000000;std::cout<<a[n];}