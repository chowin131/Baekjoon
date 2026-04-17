#import<bits/stdc++.h>
using namespace std;
main(){
    cin.tie(0)->sync_with_stdio(0);
    double t,x1,y1,x2,y2;
    cin>>t;
    while(t--){
        cin>>x1>>y1>>x2>>y2;
        double d=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
        cout<<fixed<<setprecision(6)<<acosh(1.0+d/(2.0*y1*y2))<<"\n";
    }
}