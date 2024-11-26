#include<cstdio>
#include<vector>
#define pc(x) putchar(x)
#define ls (pos<<1)
#define rs (pos<<1|1)
using ll=int;
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){f=ch=='-'?-1:f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
void write(ll x)
{
    if(x<0){x=-x;putchar('-');}
    if(x>9)write(x/10);
    putchar(x%10+48);
}
int n,m,top,cnt;ll ans[200003];
struct edge{int u,v;ll w;}e[400005];
struct STK{int id,op;}stk[400005];
int fa[400005],rev[400005],ch[400005][2],mx[400005];ll val[400005];
//LCT begin
inline void swap(int &x,int &y){x^=y;y^=x;x^=y;}
inline bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
inline void pushrev(int x){swap(ch[x][0],ch[x][1]);rev[x]^=1;}
inline void pushup(int x)
{
    mx[x]=x;
    if(ch[x][0]&&val[mx[x]]<val[mx[ch[x][0]]])mx[x]=mx[ch[x][0]];
    if(ch[x][1]&&val[mx[x]]<val[mx[ch[x][1]]])mx[x]=mx[ch[x][1]];
}
inline void pushdown(int x)
{
    if(rev[x])
    {
        if(ch[x][0])pushrev(ch[x][0]);
        if(ch[x][1])pushrev(ch[x][1]);
    }rev[x]=0;
}
inline void update(int x)
{
    if(!isroot(x))update(fa[x]);
    pushdown(x);
}
inline void rotate(int x)
{
    int y=fa[x],z=fa[y];
    int k=ch[y][1]==x,w=ch[x][k^1];
    if(!isroot(y))ch[z][ch[z][1]==y]=x;
    ch[x][k^1]=y;ch[y][k]=w;
    if(w){fa[w]=y;}fa[y]=x;fa[x]=z;
    pushup(y);
}
inline void splay(int x)
{
    update(x);
    while(!isroot(x))
    {
        int y=fa[x],z=fa[y];
        if(!isroot(y))rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
        rotate(x);
    }pushup(x);
}
inline void access(int x)
{
    for(int y=0;x;x=fa[y=x])
    {splay(x);ch[x][1]=y;pushup(x);}
}
inline void makeroot(int x){access(x);splay(x);pushrev(x);}
inline void split(int x,int y){makeroot(x);access(y);splay(y);}
inline void link(int x,int y){makeroot(x);fa[x]=y;}
inline int findroot(int x)
{
    access(x);splay(x);
    while(ch[x][0])pushdown(x),x=ch[x][0];
    splay(x);return x;
}
inline void cut(int x,int y)
{
    makeroot(x);access(y);splay(x);
    fa[y]=ch[x][1]=0;pushup(x);
}
//LCT end
ll sum;
vector<int>tr[400005];
inline void ret()
{
    int op=stk[top].op,id=stk[top].id;
    int u=e[id].u,v=e[id].v;top--;
    if(op==0)cut(u,id),cut(v,id);
    else link(u,id),link(v,id);
}
inline void modify(int pos,int l,int r,int L,int R,int id)
{
    if(L<=l&&r<=R){tr[pos].push_back(id);return;}
    int mid=(l+r)>>1;
    if(L<=mid)modify(ls,l,mid,L,R,id);
    if(R>mid)modify(rs,mid+1,r,L,R,id);
}
inline void solve(int pos,int l,int r)
{
    int nowtop=top;ll nowsum=sum;
    for(int i=0;i<(int)tr[pos].size();++i)
    {
        int id=tr[pos][i],u=e[id].u,v=e[id].v;
        split(u,v);int mxid=mx[v];
        if(val[mxid]<=val[id])continue;
        stk[++top]=(STK){mxid,1};stk[++top]=(STK){id,0};
        cut(e[mxid].u,mxid);cut(e[mxid].v,mxid);
        link(u,id);link(v,id);sum=sum-val[mxid]+val[id];
    }int mid=(l+r)>>1;
    if(l==r)ans[l]=sum; else solve(ls,l,mid),solve(rs,mid+1,r);
    sum=nowsum;while(top>nowtop)ret();
}
int main()
{
    n=read();cnt=n;
    m=read();
    for(int i=1;i<n;++i)
    {
        int u=read(),v=read(),w=read();
        e[++cnt]=(edge){u,v,w};val[cnt]=w;
        link(u,cnt);link(v,cnt);sum+=w;
    }
    for(int i=1;i<=m;++i)
    {
        int u=read(),v=read(),w=read();
        int l=i,r=m;
        e[++cnt]=(edge){u,v,w};val[cnt]=w;
        modify(1,1,m,l,r,cnt);
    }solve(1,1,m);
    for(int i=1;i<=m;++i)write(ans[i]),pc('\n');
    return 0;
}
