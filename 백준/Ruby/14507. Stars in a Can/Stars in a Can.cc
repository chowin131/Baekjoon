#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;

struct pt3 {
    ll x,y,z;
    pt3 operator-(pt3 o){return {x-o.x,y-o.y,z-o.z};}
    pt3 cross(pt3 o){return {y*o.z-z*o.y,z*o.x-x*o.z,x*o.y-y*o.x};}
    ll dot(pt3 o){return x*o.x+y*o.y+z*o.z;}
};

int n;
pt3 P[1010];

typedef array<int,3> Tri;
vector<Tri> hull;

void buildHull(){
    vector<Tri> faces;
    unordered_map<ll,int> adj;
    auto key=[](int a,int b)->ll{return (ll)a*1001+b;};
    
    auto nm=[&](int fi)->pt3{
        auto& f=faces[fi];
        return (P[f[1]]-P[f[0]]).cross(P[f[2]]-P[f[0]]);
    };
    auto vis=[&](int fi,int pi)->bool{
        return nm(fi).dot(P[pi]-P[faces[fi][0]])>0;
    };
    auto addF=[&](int a,int b,int c){
        int fi=faces.size();
        faces.push_back({a,b,c});
        adj[key(a,b)]=fi; adj[key(b,c)]=fi; adj[key(c,a)]=fi;
    };
    auto remF=[&](int fi){
        auto& f=faces[fi];
        adj.erase(key(f[0],f[1])); adj.erase(key(f[1],f[2])); adj.erase(key(f[2],f[0]));
        f={-1,-1,-1};
    };
    
    pt3 n012=(P[1]-P[0]).cross(P[2]-P[0]);
    if(n012.dot(P[3]-P[0])>0){
        addF(0,2,1); addF(0,1,3); addF(1,2,3); addF(0,3,2);
    } else {
        addF(0,1,2); addF(0,3,1); addF(1,3,2); addF(0,2,3);
    }
    
    for(int i=4;i<n;i++){
        vector<int> v;
        for(int fi=0;fi<(int)faces.size();fi++){
            if(faces[fi][0]<0) continue;
            if(vis(fi,i)) v.push_back(fi);
        }
        if(v.empty()) continue;
        set<int> vs(v.begin(),v.end());
        
        vector<pair<int,int>> horizon;
        for(int fi:v){
            for(int j=0;j<3;j++){
                int a=faces[fi][j],b=faces[fi][(j+1)%3];
                int afi=adj[key(b,a)];
                if(!vs.count(afi)) horizon.push_back({a,b});
            }
        }
        for(int fi:v) remF(fi);
        for(auto&[a,b]:horizon) addF(a,b,i);
    }
    
    hull.clear();
    for(auto& f:faces) if(f[0]>=0) hull.push_back(f);
}
struct pt2 { ld x,y; };
ld dist2(pt2 a,pt2 b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}

struct Circ { pt2 c; ld r2; };

Circ makeC2(pt2 a,pt2 b){
    pt2 c={(a.x+b.x)/2,(a.y+b.y)/2};
    return {c,dist2(c,a)};
}

Circ makeC3(pt2 a,pt2 b,pt2 c){
    ld D=2*(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y));
    ld ux=((a.x*a.x+a.y*a.y)*(b.y-c.y)+(b.x*b.x+b.y*b.y)*(c.y-a.y)+(c.x*c.x+c.y*c.y)*(a.y-b.y))/D;
    ld uy=((a.x*a.x+a.y*a.y)*(c.x-b.x)+(b.x*b.x+b.y*b.y)*(a.x-c.x)+(c.x*c.x+c.y*c.y)*(b.x-a.x))/D;
    pt2 ctr={ux,uy};
    return {ctr,dist2(ctr,a)};
}

bool inC(Circ& c,pt2 p){return dist2(c.c,p)<=c.r2+1e-10;}

Circ mec(vector<pt2> pts){
    int sz=pts.size();
    mt19937 rng(42);
    shuffle(pts.begin(),pts.end(),rng);
    Circ c={pts[0],0};
    for(int i=1;i<sz;i++){
        if(!inC(c,pts[i])){
            c={pts[i],0};
            for(int j=0;j<i;j++){
                if(!inC(c,pts[j])){
                    c=makeC2(pts[i],pts[j]);
                    for(int k=0;k<j;k++){
                        if(!inC(c,pts[k])){
                            c=makeC3(pts[i],pts[j],pts[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    
    cin>>n;
    for(int i=0;i<n;i++) cin>>P[i].x>>P[i].y>>P[i].z;
    
    buildHull();
    
    ld ans=1e30;
    const ld PI=acosl(-1.0L);
    
    for(auto& f:hull){
        pt3 nm=(P[f[1]]-P[f[0]]).cross(P[f[2]]-P[f[0]]);
        ld len=sqrtl((ld)nm.x*nm.x+(ld)nm.y*nm.y+(ld)nm.z*nm.z);
        ld nx=nm.x/len,ny=nm.y/len,nz=nm.z/len;
        
        ld baseD=nx*P[f[0]].x+ny*P[f[0]].y+nz*P[f[0]].z;
        ld minD=baseD;
        for(int i=0;i<n;i++){
            ld d=nx*P[i].x+ny*P[i].y+nz*P[i].z;
            minD=min(minD,d);
        }
        ld h=baseD-minD;
        if(h<1e-15) continue;
        pt3 ref;
        if(abs(nm.x)<=abs(nm.y)&&abs(nm.x)<=abs(nm.z)) ref={1,0,0};
        else if(abs(nm.y)<=abs(nm.z)) ref={0,1,0};
        else ref={0,0,1};
        
        pt3 ui=nm.cross(ref);
        pt3 vi=nm.cross(ui);
        
        ld ulen=sqrtl((ld)ui.x*ui.x+(ld)ui.y*ui.y+(ld)ui.z*ui.z);
        ld vlen=sqrtl((ld)vi.x*vi.x+(ld)vi.y*vi.y+(ld)vi.z*vi.z);
        ld ux=ui.x/ulen,uy=ui.y/ulen,uz=ui.z/ulen;
        ld vx=vi.x/vlen,vy=vi.y/vlen,vz=vi.z/vlen;
        
        vector<pt2> proj(n);
        for(int i=0;i<n;i++){
            proj[i]={ux*P[i].x+uy*P[i].y+uz*P[i].z,
                     vx*P[i].x+vy*P[i].y+vz*P[i].z};
        }
        
        Circ c=mec(proj);
        ld vol=PI*c.r2*h;
        ans=min(ans,vol);
    }
    
    cout<<fixed<<setprecision(8)<<ans<<"\n";
}
