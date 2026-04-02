#include <bits/stdc++.h>
#define double long double
using namespace std;
struct pos{ double x,y,z; };
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cout<<fixed;
    cout.precision(5);
    int n;
    while((cin>>n)&&(n!=0)){
        vector<pos> v(n);
        double x=0,y=0,z=0;
        for(int i=0;i<n;i++){
            cin>>v[i].x>>v[i].y>>v[i].z;
            x+=v[i].x;
            y+=v[i].y;
            z+=v[i].z;
        }
        x/=n,y/=n,z/=n;
        double ratio=0.1;
        for(int t=0;t<30000;t++){
            int idx=0;
            double max_dist_sq=0;
            for(int i=0;i<n;i++){
                double dist=(x-v[i].x)*(x-v[i].x)+(y-v[i].y)*(y-v[i].y)+(z-v[i].z)*(z-v[i].z);
                if(max_dist_sq<dist){
                    idx=i;
                    max_dist_sq=dist;
                }
            }
            pos& p=v[idx];
            x+=(p.x-x)*ratio;
            y+=(p.y-y)*ratio;
            z+=(p.z-z)*ratio;
            ratio*=0.999;
        }
        double A=0;
        for(int i=0;i<n;i++)
            A=max(A,(x-v[i].x)*(x-v[i].x)+(y-v[i].y)*(y-v[i].y)+(z-v[i].z)*(z-v[i].z));
        cout<<sqrt(A)<<'\n';
    }
}