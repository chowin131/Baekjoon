#import<bits/stdc++.h>
using namespace std;main(){double t,x1,y1,x2,y2;for(cin>>t;t--;){cin>>x1>>y1>>x2>>y2;cout<<fixed<<setprecision(6)<<acosh(1+((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/(2*y1*y2))<<"\n";}}