#include <bits/stdc++.h>
using namespace std;
#define int long long
struct pt{int x,y;};
vector<pt> P;
int dist(pt a, pt b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
int ccw(pt a, pt b, pt c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
int Euclid_min(int s,int e){
    int n=e-s+1;
    if(n<=3){
        int result=INT32_MAX;
        for(int i=s;i<=e;i++)
            for(int j=i+1;j<=e;j++)
                if(result>dist(P[i],P[j])) result=dist(P[i],P[j]);
        return result;
    }
    int mid=(s+e)/2;
    int left=Euclid_min(s,mid),right=Euclid_min(mid+1,e);
    int d=min(left,right);
    vector<pt> cross;
    for(int i=s;i<=e;i++){
        int diff=P[i].x-P[mid].x;
        if(diff*diff<d) cross.push_back(P[i]);
    }
    sort(cross.begin(),cross.end(),[&](pt a,pt b){
        if(a.y==b.y) return b.x>a.x;
        return b.y>a.y;
    });
    for(int i=0;i<cross.size();i++){
        for(int j=i+1;j<cross.size();j++){
            int diff=cross[i].y-cross[j].y;
            if(diff*diff>=d) break;
            d=min(d,dist(cross[i],cross[j]));
        }
    }
    return d;
}
int dist_che(pt a,pt b){
    return max(abs(a.x-b.x),abs(a.y-b.y));
}
bool compare_y(pt a,pt b){
    if(a.y==b.y) return b.x>a.x;
    return b.y>a.y;
}
int Ch_min(vector<pt>& Points,int s,int e){
    int n=e-s+1;
    if(n<=3){
        int result=INT32_MAX; 
        for(int i=s;i<=e;i++)
            for(int j=i+1;j<=e;j++)
                result=min(result,dist_che(Points[i],Points[j]));
        return result;
    }
    int mid=(s+e)/2;
    int left=Ch_min(Points,s,mid),right=Ch_min(Points,mid+1,e);
    int d=min(left,right);
    vector<pt> cross;
    for(int i=s;i<=e;i++){
        int diff=Points[i].x-Points[mid].x;
        if(abs(diff)<d) cross.push_back(Points[i]);
    }
    sort(cross.begin(),cross.end(),compare_y);
    for(int i=0;i<cross.size();i++){
        for(int j=i+1;j<cross.size();j++){
            int diff=cross[j].y-cross[i].y;
            if(diff>=d) break;
            d=min(d,dist_che(cross[i],cross[j]));
        }
    }
    return d;
}
main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    P.resize(n);
    for(int i=0;i<n;i++) cin>>P[i].x>>P[i].y;
    sort(P.begin(),P.end(),[&](pt a,pt b){
        if(a.x==b.x) return b.y>a.y;
        return b.x>a.x;
    });
    vector<pt> convex_hull;
    for(int i=0;i<n;i++){
        while(convex_hull.size()>=2&&ccw(convex_hull[convex_hull.size()-2],convex_hull.back(),P[i])<=0)
            convex_hull.pop_back();
        convex_hull.push_back(P[i]);
    }
    int t=convex_hull.size();
    for(int i=n-2;i>=0;i--){
        while(convex_hull.size()>t&&ccw(convex_hull[convex_hull.size()-2],convex_hull.back(),P[i])<=0)
            convex_hull.pop_back();
        convex_hull.push_back(P[i]);
    }
    convex_hull.pop_back();
    long long max_d=0;
    int j=1,size=convex_hull.size();
    for(int i=0;i<size;i++){
        int next_i=(i+1)%size;
        while(1){
            int next_j=(j+1)%size;
            pt v1,v2;
            v1.x=convex_hull[next_i].x-convex_hull[i].x;
            v1.y=convex_hull[next_i].y-convex_hull[i].y;
            v2.x=convex_hull[next_j].x-convex_hull[j].x;
            v2.y=convex_hull[next_j].y-convex_hull[j].y;
            if(ccw({0,0},v1,v2)>0) j=next_j;
            else break;
        }
        max_d=max(max_d,dist(convex_hull[i],convex_hull[j]));
    }
    cout<<max_d<<"\n"<<Euclid_min(0,n-1)<<'\n';
    
    vector<pt> P_man(n);
    int min_u=LLONG_MAX,max_u=LLONG_MIN;
    int min_v=LLONG_MAX,max_v=LLONG_MIN;
    for(int i=0;i<n;i++){
        int u=P[i].x+P[i].y;
        int v=P[i].x-P[i].y;
        P_man[i]={u,v};
        min_u=min(min_u,u);
        max_u=max(max_u,u);
        min_v=min(min_v,v);
        max_v=max(max_v,v);
    }
    int max_man=max(max_u-min_u,max_v-min_v);
    sort(P_man.begin(),P_man.end(),[&](pt a,pt b){
        if(a.x==b.x) return b.y>a.y;
        return b.x>a.x;
    });
    int min_man=Ch_min(P_man,0,n-1);
    cout<<max_man<<"\n"<<min_man<<'\n'; 
    int min_x=P[0].x,max_x=P.back().x;
    sort(P.begin(),P.end(),compare_y);
    int min_y=P[0].y,max_y=P.back().y;
    sort(P.begin(),P.end(),[&](pt a,pt b){
        if(a.x==b.x) return b.y>a.y;
        return b.x>a.x;
    });
    cout<<max(max_x-min_x,max_y-min_y)<<'\n'<<Ch_min(P,0,n-1);
}