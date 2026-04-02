#include <bits/stdc++.h>
using namespace std;
#define eps 1e-9
#define double long double
struct pt{ double x,y,z; };
struct sphere{ pt ct; double r; };

double dist_sq(pt a,pt b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z);
}

sphere make_sphere(const vector<pt>& R){
    if(R.empty()) return {{0,0,0},0};
    else if(R.size()==1) return {R[0],0};
    else if(R.size()==2){
        pt center={(R[0].x+R[1].x)/2.0,(R[0].y+R[1].y)/2.0,(R[0].z+R[1].z)/2.0};
        double radius=sqrt(dist_sq(R[0],R[1]))/2.0;
        return {center,radius};
    }
    else if(R.size()==3){
        sphere s1=make_sphere({R[0],R[1]});
        if(dist_sq(R[2],s1.ct)<s1.r*s1.r+eps) return s1;
        sphere s2=make_sphere({R[0],R[2]});
        if(dist_sq(R[1],s2.ct)<s2.r*s2.r+eps) return s2;
        sphere s3=make_sphere({R[1],R[2]});
        if(dist_sq(R[0],s3.ct)<s3.r*s3.r+eps) return s3;

        pt p1=R[0],p2=R[1],p3=R[2];
        pt u={p2.x-p1.x,p2.y-p1.y,p2.z-p1.z};
        pt v={p3.x-p1.x,p3.y-p1.y,p3.z-p1.z};
        pt n={u.y*v.z-u.z*v.y,u.z*v.x-u.x*v.z,u.x*v.y-u.y*v.x};
        
        double A[3][3],B[3];
        A[0][0]=n.x; A[0][1]=n.y; A[0][2]=n.z;
        A[1][0]=u.x; A[1][1]=u.y; A[1][2]=u.z;
        A[2][0]=v.x; A[2][1]=v.y; A[2][2]=v.z;
        
        B[0]=n.x*p1.x+n.y*p1.y+n.z*p1.z;
        B[1]=u.x*(p1.x+p2.x)/2.0+u.y*(p1.y+p2.y)/2.0+u.z*(p1.z+p2.z)/2.0;
        B[2]=v.x*(p1.x+p3.x)/2.0+v.y*(p1.y+p3.y)/2.0+v.z*(p1.z+p3.z)/2.0;
        
        double det_A=A[0][0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1])-A[0][1]*(A[1][0]*A[2][2]-A[1][2]*A[2][0])+A[0][2]*(A[1][0]*A[2][1]-A[1][1]*A[2][0]);
        
        if(abs(det_A)<eps) return {{0,0,0},1e18};

        double det_Ax=B[0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1])-A[0][1]*(B[1]*A[2][2]-A[1][2]*B[2])+A[0][2]*(B[1]*A[2][1]-A[1][1]*B[2]);
        double det_Ay=A[0][0]*(B[1]*A[2][2]-A[1][2]*B[2])-B[0]*(A[1][0]*A[2][2]-A[1][2]*A[2][0])+A[0][2]*(A[1][0]*B[2]-B[1]*A[2][0]);
        double det_Az=A[0][0]*(A[1][1]*B[2]-B[1]*A[2][1])-A[0][1]*(A[1][0]*B[2]-B[1]*A[2][0])+B[0]*(A[1][0]*A[2][1]-A[1][1]*A[2][0]);

        pt center={det_Ax/det_A,det_Ay/det_A,det_Az/det_A};
        return {center,sqrt(dist_sq(center,p1))};
    }

    pt p[4]={R[0],R[1],R[2],R[3]};
    double A[3][3],B[3];
    for(int i=0;i<3;i++){
        A[i][0]=2*(p[i+1].x-p[0].x);
        A[i][1]=2*(p[i+1].y-p[0].y);
        A[i][2]=2*(p[i+1].z-p[0].z);
        B[i]=(p[i+1].x*p[i+1].x-p[0].x*p[0].x)+(p[i+1].y*p[i+1].y-p[0].y*p[0].y)+(p[i+1].z*p[i+1].z-p[0].z*p[0].z);
    }
    double det_A=A[0][0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1])-A[0][1]*(A[1][0]*A[2][2]-A[1][2]*A[2][0])+A[0][2]*(A[1][0]*A[2][1]-A[1][1]*A[2][0]);

    if(abs(det_A)<eps){
        sphere best_sphere={{0,0,0},1e18};
        for(int i=0;i<4;i++){
            for(int j=i+1;j<4;j++){
                sphere s=make_sphere({R[i],R[j]});
                bool is_valid=true;
                for(int k=0;k<4;k++){
                    if(dist_sq(R[k],s.ct)>s.r*s.r+eps){is_valid=false; break;}
                }
                if(is_valid&&s.r<best_sphere.r) best_sphere=s;
            }
        }
        for(int i=0;i<4;i++){
            vector<pt> T;
            for(int j=0;j<4;j++) if(i!=j) T.push_back(R[j]);
            sphere s=make_sphere(T);
            bool is_valid=true;
            for(int k=0;k<4;k++){
                if(dist_sq(R[k],s.ct)>s.r*s.r+eps){is_valid=false; break;}
            }
            if(is_valid&&s.r<best_sphere.r) best_sphere=s;
        }
        return best_sphere;
    }
    double det_Ax=B[0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1])-A[0][1]*(B[1]*A[2][2]-A[1][2]*B[2])+A[0][2]*(B[1]*A[2][1]-A[1][1]*B[2]);
    double det_Ay=A[0][0]*(B[1]*A[2][2]-A[1][2]*B[2])-B[0]*(A[1][0]*A[2][2]-A[1][2]*A[2][0])+A[0][2]*(A[1][0]*B[2]-B[1]*A[2][0]);
    double det_Az=A[0][0]*(A[1][1]*B[2]-B[1]*A[2][1])-A[0][1]*(A[1][0]*B[2]-B[1]*A[2][0])+B[0]*(A[1][0]*A[2][1]-A[1][1]*A[2][0]);

    pt center={det_Ax/det_A,det_Ay/det_A,det_Az/det_A};
    return {center,sqrt(dist_sq(center,p[0]))};
}

sphere welzl(vector<pt>& P,vector<pt> R,int remain){
    if(remain==0||R.size()==4)
        return make_sphere(R);

    pt p=P[remain-1];
    sphere mec=welzl(P,R,remain-1);

    if(dist_sq(p,mec.ct)<mec.r*mec.r+eps)
        return mec;

    R.push_back(p);
    return welzl(P,R,remain-1);
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    int n;
    cin>>n;
    vector<pt> points(n);
    for(int i=0;i<n;i++)
        cin>>points[i].x>>points[i].y>>points[i].z;
    
    unsigned seed=chrono::system_clock::now().time_since_epoch().count();
    shuffle(points.begin(),points.end(),default_random_engine(seed));

    sphere result=welzl(points,{},n);
    
    if(abs(result.ct.x)<eps) result.ct.x=0.0;
    if(abs(result.ct.y)<eps) result.ct.y=0.0;
    if(abs(result.ct.z)<eps) result.ct.z=0.0;
    
    cout<<fixed;
    cout.precision(2);
    cout<<result.r;
}