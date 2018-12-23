#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int>ii;
typedef vector<ii> vii;
const int mx=1e5+4;
const int INF=2e5+9;
set <int> g[mx];
int dp[mx][20],lv[mx],sub[mx],n,ans[mx],par[mx];
void dfs0(int u,int p)
{
    for(auto it=g[u].begin();it!=g[u].end();it++){
        if(*it!=p){
            dp[*it][0]=u;
            lv[*it]=lv[u]+1;
            dfs0(*it,u);
        }
    }
}
preprocess()
{
    lv[1]=0;
    memset(dp,-1,sizeof dp);
    dfs0(1,-1);
    for(int j=1; (1<<j)<n;j++){
        for(int i=1;i<=n;i++)
            if(dp[i][j-1]!=-1) dp[i][j]=dp[ dp[i][j-1] ][j-1];
    }
}
int lca(int p,int q)
{
    if(lv[p]<lv[q]) swap(p,q);
    int log=1;
    while(1){
        int next=log+1;
        if( (1<<next)>lv[p]) break;
        log++;
    }
    for(int i=log;i>=0;i--)
        if(lv[p]-(1<<i)>=lv[q]) p=dp[p][i];
    if(p==q) return p;
    for(int i=log;i>=0;i--){
        if(dp[p][i]!=-1 && dp[p][i]!=dp[q][i])
            p=dp[p][i],q=dp[q][i];
    }
    return dp[p][0];
}
int distt(int a,int b){
    return lv[a]+lv[b]-2*lv[lca(a,b)];}
/*  Decomposition part */
int nn=0;
void dfs1(int u,int p)
{
    sub[u]=1;
    nn++;
    for(auto it=g[u].begin();it!=g[u].end();it++){
        if(*it!=p){
            dfs1(*it,u);
            sub[u]+=sub[*it];
        }
    }
}
int dfs2(int u,int p)
{
    for(auto it=g[u].begin();it!=g[u].end();it++){
        if(*it!=p && sub[*it]>nn/2){
            return dfs2(*it,u);
        }
    }
    return u;
}
void decompose(int r,int p)
{
    nn=0;
    dfs1(r,r);
    int centroid = dfs2(r,r);
    if(p==-1) p=centroid;
    par[centroid]=p;
    for(auto it=g[centroid].begin();it!=g[centroid].end();it++){
        g[*it].erase(centroid);
        decompose(*it,centroid);
    }
    g[centroid].clear();
}
/* querry */
void update(int u)
{
    int x=u;
    while(1){
        ans[x]=min(ans[x],distt(x,u));
        if(x==par[x]) break;
        x=par[x];
    }
}
int querry(int u)
{
    int x=u;
    int ret=INF;
    while(1){
        ret=min(ret,distt(x,u)+ans[x]);
        if(x==par[x]) break;
        x=par[x];
    }
    return ret;
}
int main()
{
    int m,i,u,v;
    cin>>n>>m;
    for(i=1;i<n;i++){
        cin>>u>>v;
        g[u].insert(v);
        g[v].insert(u);
    }
    preprocess();
    decompose(1,-1);
    for(i=1;i<=n;i++) ans[i]=INF;
    update(1);
    while(m--){
        cin>>u>>v;
        if(u==1)
            update(v);
        else
            cout<<querry(v)<<endl;
    }
    return 0;
}
