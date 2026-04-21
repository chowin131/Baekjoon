#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
using p=pair<int,int>;
#define f first
#define s second
int t_id[3075][3],t_a[3075][3];
int dp[2][3075],p_id[5005][3075];
char p_nb[5005][3075];

int enc(int b,vector<int>& df){
    int r=b;
    for(int d:df)r=r*4+d;
    return r;
}
void dec(int id,int&b,vector<int>& df){
    df.resize(5);
    for(int i=4;i>=0;--i){df[i]=id%4;id/=4;}
    b=id;
}
void pre(){
    for(int id=0;id<3072;++id){
        int b;vector<int> df;dec(id,b,df);
        vector<int> o(11);o[0]=0;
        for(int j=0;j<5;++j)o[j+1]=o[j]+df[j];
        for(int j=5;j<10;++j)o[j+1]=o[j]+3;
        for(int nb=0;nb<3;++nb){
            vector<int> nw(6,1e9);
            for(int k=0;k<6;++k){
                int vn=nb+3*k;
                for(int j=0;j<=10;++j){
                    int vo=b+3*j,c=o[j]+max(0LL,vn-vo);
                    if(c<nw[k])nw[k]=c;
                }
            }
            t_a[id][nb]=nw[0];
            vector<int> ndf(5);
            for(int k=0;k<5;++k)ndf[k]=nw[k+1]-nw[k];
            t_id[id][nb]=enc(nb,ndf);
        }
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    pre();
    for(int id=0;id<3072;++id)dp[0][id]=-1;
    for(int b1=0;b1<3;++b1){
        vector<int> tv={3,3,3,3,3};
        int id=enc(b1,tv);
        dp[1][id]=b1;
        p_id[1][id]=-1;
        p_nb[1][id]=b1;
    }
    for(int i=1;i<n;++i){
        int c=i%2,nx=(i+1)%2;
        for(int id=0;id<3072;++id)dp[nx][id]=-1;
        for(int id=0;id<3072;++id){
            if(dp[c][id]==-1)continue;
            for(int nb=0;nb<3;++nb){
                int nid=t_id[id][nb],nc=dp[c][id]+t_a[id][nb];
                if(nc>dp[nx][nid]){
                    dp[nx][nid]=nc;
                    p_id[i+1][nid]=id;
                    p_nb[i+1][nid]=nb;
                }
            }
        }
    }
    int bid=-1,mx=-1;
    for(int id=0;id<3072;++id)
        if(dp[n%2][id]>mx){
            mx=dp[n%2][id];
            bid=id;
        }
    vector<int> b(n+1);int cid=bid;
    for(int i=n;i>=1;--i){
        b[i]=p_nb[i][cid];
        cid=p_id[i][cid];
    }
    for(int i=1;i<=n;++i){
        int a=(3-b[i])%3;if(a==0)a=3;
        cout<<a<<(i==n?"":" ");
    }
    cout<<"\n"<<mx<<"\n";
    int mv=min(15005LL,3*n+5);
    vector<int> cst(mv,1e9);
    vector<vector<short>> tr(n+2,vector<short>(mv,-1));
    cst[0]=0;
    vector<int> ncst(mv),pm(mv),pi(mv),sm(mv),si(mv);
    for(int i=1;i<=n+1;++i){
        int tm=(i<=n)?b[i]:0;
        int mn=1e9,idx=-1;
        for(int u=0;u<mv;++u){
            if(cst[u]-u<mn){
                mn=cst[u]-u;
                idx=u;
            }
            pm[u]=mn;
            pi[u]=idx;
        }
        mn=1e9;
        idx=-1;
        for(int u=mv-1;u>=0;--u){
            if(cst[u]<mn){
                mn=cst[u];
                idx=u;
            }
            sm[u]=mn;si[u]=idx;
        }
        fill(ncst.begin(),ncst.end(),1e9);
        for(int v=tm;v<mv;v+=3){
            int c1=v+pm[v],c2=(v+1<mv)?sm[v+1]:1e9;
            if(c1<=c2){
                ncst[v]=c1;
                tr[i][v]=pi[v];
            }
            else{
                ncst[v]=c2;
                tr[i][v]=si[v+1];
            }
        }
        cst=ncst;
    }
    vector<int> pt(n+2);
    pt[n+1]=0;
    int cv=0;
    for(int i=n+1;i>=1;--i){
        cv=tr[i][cv];
        pt[i-1]=cv;
    }
    vector<int> st;
    vector<p> ops;
    for(int i=1;i<=n+1;++i){
        int df=pt[i]-pt[i-1];
        if(df>0)for(int k=0;k<df;++k)st.push_back(i);
        else if(df<0)for(int k=0;k<-df;++k){
            int s=st.back();
            st.pop_back();
            ops.push_back({s,i-1});
        }
    }
    for(auto& op:ops)cout<<op.f<<" "<<op.s<<"\n";
    return 0;
}