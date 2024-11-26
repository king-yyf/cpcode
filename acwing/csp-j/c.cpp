#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2;
LL mod = 1000000007;
int cnt,ct;
LL pri[2005];
LL num[2005];
struct Matrix
{
    LL m[N][N];
} ;
Matrix A;
Matrix I = {1, 0, 0, 1};
char str[1000005];
map<int,int>y;
int flag=0;
Matrix multi(Matrix a,Matrix b)
{
    Matrix c;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            c.m[i][j]  =0;
            for(int k=0; k<N; k++)
            {
                c.m[i][j] =(c.m[i][j]+a.m[i][k] * b.m[k][j]%mod)%mod;
            }
        }
    }
    return c;
}
Matrix power(Matrix A,LL n)
{
    Matrix ans = I, p = A;
    while(n>0)
    {
        if(n & 1)
        {
            ans = multi(ans,p);
            n--;
        }
        n >>= 1;
        p = multi(p,p);
    }
    return ans;
}
LL quick_mod(LL a,LL b,LL MOD)
{
    LL ans = 1;
    a %= MOD;
    while(b>0)
    {
        if(b & 1)
        {
            ans = ans * a % MOD;
            b--;
        }
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
LL quick_mul(LL a,LL b,LL MOD)
{
    LL ans=0;
    while(b)
    {
        if(b&1)
        {
            ans=ans+a;
            if(ans>MOD)
            {
                ans%=MOD;
                flag=1;
            }
        }
        a=a+a;
        if(a>MOD)
        {
            a%=MOD;
            flag=1;
        }
        b=b/2;
    }
    return ans;
}
LL Legendre(LL a,LL p,LL MOD)
{
    LL t = quick_mod(a,(p-1)>>1,MOD);
    if(t == 1) return 1;
    return -1;
}
void yinzi(LL x)
{
    for(int i=2; i*i<=x; i++)
    {
        if(x%i==0)
        {
            while(x%i==0)
            {
                y[i]++;
                x=x/i;
            }
        }
    }
    if(x>1)
    {
        y[x]++;
    }
}
LL lcm(LL a,LL b)
{
    return a/gcd(a,b)*b;
}
LL get_len(LL a,LL b,LL mod)
{
    yinzi(mod);
    for(map<int,int>::iterator i=y.begin(); i!=y.end(); i++)
    {
        pri[cnt]=i->first;
        num[cnt]=i->second;
        cnt++;
    }
    LL ans=1;
    LL c=a*a+4*b;
    for(int i=0; i<cnt; i++)
    {
        LL p=1;
        if(pri[i]==2)
        {
            p*=3;
            for(int j=0; j<=num[i]; j++)
                p*=pri[i];
        }
        else if(c%pri[i]==0)
        {
            p*=pri[i]*(pri[i]-1);
            for(int j=1; j<num[i]; j++)
                p*=pri[i];
        }
        else if(Legendre(c,pri[i],pri[i])==1)
        {
            p*=(pri[i]-1);
            for(int j=1; j<num[i]; j++)
                p*=pri[i];
        }
        else
        {
            p*=(pri[i]-1)*(pri[i]+1);
            for(int j=1; j<num[i]; j++)
                p*=pri[i];
        }
        ans=lcm(ans,p);
    }
    return ans;
}
int main()
{

    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    LL a,b,c,d;
    cin>>c>>d>>a>>b;//x0,x1,p,q
    int k;
    cin>>mod>>k>>str;
    LL p=get_len(a,b,mod);
    LL n=0;
    int len=strlen(str);
    for(int i=0; i<len; i++)
    {
        n=(n*10+str[i]-'0')%p;
    }
    n=(n+p+1)%p;
    A.m[0][0]=a;
    A.m[0][1]=b;
    A.m[1][0]=1;
    A.m[1][1]=0;
    Matrix T=power(A,n-1);
    long long p1=(T.m[0][0]*d%mod+T.m[0][1]*c%mod)%mod;
    printf("%lld\n",p1);


    if(k>=2){
        n=(n+p+1)%p;
        A.m[0][0]=a;
        A.m[0][1]=b;
        A.m[1][0]=1;
        A.m[1][1]=0;
        Matrix T=power(A,n-1);
        long long p2=(T.m[0][0]*d%mod+T.m[0][1]*c%mod)%mod;
        printf("%lld\n",p2);
        for(int i=3;i<=k;++i){
            long long p3=(a*p2+b*p1)%mod;
            printf("%lld\n",p3);
            p1=p2;
            p2=p3;
        }
    }


    
    return 0;
}




