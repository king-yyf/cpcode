#include<bits/stdc++.h>
using namespace std;
bool MillerRabin(long long n,vector<long long> A){
  long long D=n-1,s=0,t,d;
  uint64_t x,mod=n,imod=n,t128=-__uint128_t(n)%n,rx,ry;
  for(;D%2==0;D>>=1) s++;
  for(int i=0;i<5;i++) imod*=2-mod*imod;
  for(auto a:A){
    if(n<=a) return true;
    for(x=1,d=D;d>0;d>>=1){
      if(d&1){
        rx=(__uint128_t(a)*x+__uint128_t(uint64_t(__uint128_t(a)*x)*uint64_t(-imod))*mod)>>64;
        rx=rx>=mod?rx-mod:rx;
        ry=(__uint128_t(rx)*t128+__uint128_t(uint64_t(__uint128_t(rx)*t128)*uint64_t(-imod))*mod)>>64;
        ry=ry>=mod?ry-mod:ry;
        x=ry;
      }
      rx=(__uint128_t(a)*a+__uint128_t(uint64_t(__uint128_t(a)*a)*uint64_t(-imod))*mod)>>64;
      rx=rx>=mod?rx-mod:rx;
      ry=(__uint128_t(rx)*t128+__uint128_t(uint64_t(__uint128_t(rx)*t128)*uint64_t(-imod))*mod)>>64;
      ry=ry>=mod?ry-mod:ry;
      a=ry;
    }
    if(x!=1){
      for(t=0;t<s;t++){
        if(x==n-1) break;
        rx=(__uint128_t(x)*x+__uint128_t(uint64_t(__uint128_t(x)*x)*uint64_t(-imod))*mod)>>64;
        rx=rx>=mod?rx-mod:rx;
        ry=(__uint128_t(rx)*t128+__uint128_t(uint64_t(__uint128_t(rx)*t128)*uint64_t(-imod))*mod)>>64;
        ry=ry>=mod?ry-mod:ry;
        x=ry;
      }
      if(t==s) return false;
    }
  }
  return true;
}
bool isprime(long long n){
  if(n<=1) return false;
  else if(n==2) return true;
  else if(n%2==0) return false;
  else if(n<4759123141LL) return MillerRabin(n,{2,7,61});
  else return MillerRabin(n,{2,325,9375,28178,450775,9780504,1795265022});
}
int main(){
  std::cin.tie(0)->sync_with_stdio(0);
  int q;
  cin>>q;
  while(q-->0){
    long long n;
    cin>>n;
    cout<<(isprime(n)?"Yes":"No")<<endl;
  }
}