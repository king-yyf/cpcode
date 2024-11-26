#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long LL;

LL prime[9]={2,3,5,7,11,13,17,19,23},n,a[105];
int a1;

LL gcd(LL x,LL y)
{
    if (!y) return x;
    else return gcd(y,x%y);
}

LL mul(LL x,LL y,LL mo)
{
    LL tmp=(x*y-(LL)((double)x*y/mo+0.1)*mo)%mo;
    if (tmp<0) tmp+=mo;
    return tmp;
}

LL ksm(LL x,LL y,LL mo)
{
    LL ans=1;
    while (y)
    {
        if (y&1) ans=mul(ans,x,mo);
        x=mul(x,x,mo);y>>=1;
    }
    return ans;
}

bool MR(LL n)
{
    if (n==2) return 1;
    if (n%2==0) return 0;
    int lg=0;LL w=n-1;
    while (w%2==0) lg++,w/=2;
    for (int i=0;i<9;i++)
    {
        if (n==prime[i]) return 1;
        LL x=ksm(prime[i],w,n);
        if (x==1||x==n-1) continue;
        for (int j=1;j<=lg;j++)
        {
            LL y=mul(x,x,n);
            if (x!=1&&x!=n-1&&y==1) return 0;
            x=y;
        }
        if (x!=1) return 0;
    }
    return 1;
}

LL rho(LL n)
{
    LL c=rand()*rand()%(n-1)+1,x1=rand()*rand()%n,x2=x1,k=2,p=1;
    for (int i=1;p==1;i++)
    {
        x1=(mul(x1,x1,n)+c)%n;
        if (x1==x2) return 1;
        p=gcd(n,abs(x1-x2));
        if (i==k) k<<=1,x2=x1;
    }
    return p;
}

void divi(LL n)
{
    if (n==1) return;
    if (MR(n))
    {
        a[++a1]=n;return;
    }
    LL p=1;
    while (p==1) p=rho(n);
    divi(p);divi(n/p);
}

int main()
{
    scanf("%lld",&n);
    long long m=n;
    divi(n);
    sort(a+1,a+a1+1);
    a1=unique(a+1,a+a1+1)-a-1;
    // for(int i=1;i<=a1;++i){
    //     cout<<a[i]<<" \n"[i==n];
    // }
    // cout<<n<<"\n";
    for (int i=1;i<=a1;i++) n=n/a[i]*(a[i]-1);
    if(a1==1&&a[1]==m) cout<<"Bob win"<<"\n";
    else  cout<<"Alice win"<<"\n";
    return 0;
}