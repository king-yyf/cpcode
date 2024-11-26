#include<bits/stdc++.h>
#define N 20005
#define int long long
using namespace std;
int n,m,p;
int a[N*4];
int sum[N*4];
struct P{
    int add,mul;
}tag[N*4];
void pushup(int x){
    sum[x]=(sum[x<<1]+sum[x<<1|1]);
}
void build(int x,int l,int r){//建树
    if(l==r){
        sum[x]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
void pushdown(int x,int l,int r){
    int ls=x<<1,rs=x<<1|1,mid=(l+r)>>1;
    sum[ls]=(sum[ls]*tag[x].mul+tag[x].add*(mid-l+1));
    tag[ls].mul=(tag[ls].mul*tag[x].mul);
    tag[ls].add=(tag[ls].add*tag[x].mul+tag[x].add);
    
    sum[rs]=(sum[rs]*tag[x].mul+tag[x].add*(r-(mid+1)+1));
    tag[rs].mul=(tag[rs].mul*tag[x].mul);
    tag[rs].add=(tag[rs].add*tag[x].mul+tag[x].add);
    
    tag[x].add=0;tag[x].mul=1;
    return;
}
void updata_mul(int x,int l,int r,int ll,int rr,int k){
    if(r<ll || l>rr) return;
    if(l>=ll && r<=rr){
        sum[x]=(sum[x]*k);
        tag[x].mul=(tag[x].mul*k);
        tag[x].add=(tag[x].add*k);
        return;
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    updata_mul(x<<1,l,mid,ll,rr,k);
    updata_mul(x<<1|1,mid+1,r,ll,rr,k);
    pushup(x);
}
void updata_add(int x,int l,int r,int ll,int rr,int k){
    if(r<ll || l>rr) return;
    if(l>=ll && r<=rr){
        sum[x]=(sum[x]+k*(r-l+1));
        tag[x].add=(tag[x].add+k);
        return;
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    updata_add(x<<1,l,mid,ll,rr,k);
    updata_add(x<<1|1,mid+1,r,ll,rr,k);
    pushup(x);
}
int query(int x,int l,int r,int ll,int rr){
    if(r<ll || l>rr) return 0;
    if(l>=ll && r<=rr){
        return sum[x];
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    return (query(x<<1,l,mid,ll,rr)+query(x<<1|1,mid+1,r,ll,rr));
}
signed main(){
    scanf("%lld %lld %lld",&n,&m,&p);
    for(int i=1;i<=4*n;i++) tag[i].mul=1;//注意乘法标记初始化为1
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    build(1,1,n);
    int opt,x,y,k;
    while(m--){
        scanf("%lld",&opt);
        if(opt==1){
            scanf("%lld %lld %lld",&x,&y,&k);
            updata_mul(1,1,n,x,y,k);
        }
        if(opt==2){
            scanf("%lld %lld %lld",&x,&y,&k);
            updata_add(1,1,n,x,y,k);
        }
        if(opt==3){
            scanf("%lld %lld",&x,&y);
            cout<<query(1,1,n,x,y)<<endl;
        }
        
    }
    return 0;
}