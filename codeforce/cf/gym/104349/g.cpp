#include<cstdio>
#include<iostream>
#include<cstring>
#define RI  int
#define CI const int&
using namespace std;
const int N=505,mod=1e9+7;
int n,a[N],f[N][N],C[N][N];
inline int DP(CI l,CI r)
{
    if (l>r) return 1; if (~f[l][r]) return f[l][r]; int ret=0;
    for (RI i=l+1;i<=r;++i) if ((i-l+1)%2==0&&a[l]>a[i])
    (ret+=1LL*DP(l+1,i-1)*DP(i+1,r)%mod*C[(i-l+1)/2+(r-i)/2][(r-i)/2]%mod)%=mod;
    return f[l][r]=ret;
}
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    RI i,j; for (scanf("%d",&n),i=1;i<=n;++i) scanf("%d",&a[i]);
    for (C[0][0]=i=1;i<=n;++i) for (C[i][0]=j=1;j<=i;++j)
    C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    return memset(f,-1,sizeof(f)),printf("%d",DP(1,n)),0;
}