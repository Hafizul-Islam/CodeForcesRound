/*
    convex hull optimization tricks
    ECR-11
    Accepted
    Md Hafizul islam
*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int mx=200000+3;
ll a[mx],s[mx],p[mx];
vi mi,bi;
bool chack(int f1,int f2,int f3)
{
    return 1.0*(bi[f3]-bi[f1])*(mi[f1]-mi[f2]) < 1.0*(bi[f2]-bi[f1])*(mi[f1]-mi[f3]);
}
void add(ll m,ll b)
{
    mi.pb(m);
    bi.pb(b);
    int sz=mi.size();
    while(sz>=3 && chack(sz-1,sz-2,sz-3)){
        mi.erase(mi.end()-2);
        bi.erase(bi.end()-2);
        sz--;
    }
}
ll f(int i,ll x) { return mi[i]*x+bi[i]; }
ll query(ll x)
{
    if(!mi.size()) return 0;
    int l=0,r=mi.size()-1,idx=0;
    while(l<=r){
        int del = (r-l)/3;
        int m1 = l+del;
        int m2 = r-del;
        if( f(m1,x) > f(m2,x) ){
            r=m2-1; idx=m1;
        }else{
            l=m1+1,idx=m2;
        }
    }
    return f(idx,x);
}
int main()
{
    int n,i;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
        p[i]=p[i-1]+a[i];
        s[i]=s[i-1]+a[i]*i;
    }
    ll Maxx=0;
    add(0,0);
    for(i=1;i<=n;i++){
        Maxx=max(Maxx,query(p[i])+s[i]);
        add(-i,i*p[i]-s[i]);
    }
    cout<<Maxx<<endl;
    return 0;
}
