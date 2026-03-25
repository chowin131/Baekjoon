#import<iostream>
long long a[2000001]={0,1},n,i;main(){std::cin>>n,n%=1500000;for(i=2;i<=n;i++)a[i]=(a[i-1]+a[i-2])%1000000;std::cout<<a[n];}