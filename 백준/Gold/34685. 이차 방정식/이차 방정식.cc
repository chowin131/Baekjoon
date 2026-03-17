#import<bits/stdc++.h>
long k,S,i;main(){for(std::cin>>k;++i<=abs(k);S+=2*(k*k%i==0));std::cout<<S<<' '<<S*2*k;}