
/*

Consider bit mask dp, transfer from top to bottom.

we make dp[bitmask][i] = the number of possible solutions for the i-th line bitmask

In order to prevent the occurrence of two adjacent 1s, we need to ensure that there are no two adjacent 1s in the binary of the bitmask, and that the bit-and value of the two bitmasks during the transition must also be zero.

assuming that the two bitmasks transferred are a and b, then we have a&b=0, It can be obtained that a is a subset of ~b(Flip each bit of b), Then we can first perform SOS-DP, obtain the answer, and reverse it.

Code

*/

#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
// #define int long long
long long power(long long x,long long p,long long mod) {
   long long answer=1;x%=mod;
   while(p) {
      if(p&1)
         answer=answer*x%mod;
      x=x*x%mod;
      p>>=1;
   }
   return answer;
}
const int MOD=998244353;
char a[15][15];
int n,m,ok[32768],dp[32768][2],s,cnt;
void Delta() {
   cin >> n >> m;
   for(int i=0;i<(1<<max(n,m));++i) {
      ok[i]=true;
      for(int j=0;j<max(n,m);++j)
         if((i>>j)%4==3)
            ok[i]=false;
   }
   for(int i=0;i<n;++i)
      for(int j=0;j<m;++j) {
         cin >> a[i][j];
         cnt+=a[i][j]=='?';
      }
   for(int i=0;i<(1<<m);++i) dp[i][0]=ok[i];
   for(int i=0;i<m;++i)
      if(a[0][i]!='?')
         for(int j=0;j<(1<<m);++j)
            if((j>>i)%2!=a[0][i]-'0')
               dp[j][0]=0;
   for(int i=1;i<n;++i) {
      for(int j=0;j<(1<<m);++j) dp[j][i%2]=dp[j][(i-1)%2];
      for(int j=0;j<m;++j)
         for(int k=0;k<(1<<m);++k)
            if(k&(1<<j))
               dp[k][i%2]=(dp[k][i%2]+dp[k^(1<<j)][i%2])%MOD;
      for(int j=0;j<(1<<(m-1));++j)
         swap(dp[j][i%2],dp[(1<<m)-j-1][i%2]);
      for(int j=0;j<m;++j)
         if(a[i][j]!='?')
            for(int k=0;k<(1<<m);++k)
               if((k>>j)%2!=a[i][j]-'0')
                  dp[k][i%2]=0;
      for(int j=0;j<(1<<m);++j)
         if(!ok[j])
            dp[j][i%2]=0;
   }
   for(int i=0;i<(1<<m);++i)
      s=(s+dp[i][(n-1)%2])%MOD;
   cout << power(499122177,cnt,MOD)*s%MOD << endl;
}
signed main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0);cout.tie(0);
   Delta();
}