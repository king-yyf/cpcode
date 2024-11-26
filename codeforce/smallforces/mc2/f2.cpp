#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>

using namespace std;
long long mod=1e9+7;
long long fre[200005];
long long sz[200005];
long long deg[200005];
long long sef[200005];
long long ponder[200005];
long long Y[200005];
long long X[200005];
long long find(long long u)
{
    if(u==sef[u])
    {
        return u;
    }
    return sef[u]=find(sef[u]);
}
void merge(long long x,long long y)
{
    x=find(x);
    y=find(y);
    if(x!=y)
    {
        sef[y]=x;
        ponder[x]+=ponder[y];
        sz[x]+=sz[y];
    }
}
int main()
{
    long long n,i,j,l,z,m,a,t=1,h,poz1,poz2,x,y,c,d,c1,c2,nra,nrc,sol,x2,y2,op,q,tip,gc,prod,u,dr,st,diffst,diffdr,ramase,cate,curr,rez,rad,rest,ultimu,primu,leng,e,f,semn,poz,b,w;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    t=1;
    string s;
    string s1;
    char ch;
    long long minim=2*-1e9;
    pair<long long,long long>rasp;
    t=1;
    cin>>t;
    for(op=1;op<=t;op++)
    {
        cin>>n>>m;
        for(i=1;i<=n;i++)
        {
            deg[i]=0;
        }
        for(i=1;i<=m;i++)
        {
            cin>>x>>y>>w;
            deg[x]+=w;
            deg[y]+=w;
            X[i]=x;
            Y[i]=y;
        }
        for(i=1;i<=n;i++)
        {
            fre[i]=0;
            sz[i]=1;
            sef[i]=i;
            ponder[i]=deg[i]%2;
        }
        for(i=1;i<=m;i++)
        {
            merge(X[i],Y[i]);
        }
        long long nr=0;
        for(i=1;i<=n;i++)
        {
            x=find(i);
            if(fre[x]==0)
            {
                nr=nr+ponder[x]/2;
                if(ponder[x]==0 && sz[x]>=2)
                {
                    nr++;
                }
            }
            fre[x]=1;
        }
        cout<<nr<<'\n';
    }
    return 0;
}
