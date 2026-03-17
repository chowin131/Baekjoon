#import<bits/stdc++.h>
long k,S,i;main(){std::cin>>k;for(;++i<=abs(k);)if(k*k%i==0)S+=2;std::cout<<S<<' '<<S*2*k;}