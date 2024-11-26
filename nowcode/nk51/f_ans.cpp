#include<bits/stdc++.h>
using namespace std;
using ll=long long;


const ll mod=1e9+7;
ll qp(ll a,ll b,ll p=mod){
	ll ans=1;
	while(b){
		if(b&1)	ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}

ll n,a[100010],pre[100010],sum[100010];

long long  qpow(long long m, long long k, long long p) {
    long long res = 1 % p, t = m;
    while (k) {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}
int main(){
	cin>>n;
	rep(i,1,n){
		scanf("%lld",&a[i]);
		pre[i]=(pre[i-1]+a[i])%mod;
	}
	rep(l,1,n){
		if(l<=n/2+n%2){
			sum[l]=(sum[l-1]+(pre[n+1-l]-pre[l-1]+mod))%mod;
		}
		else{
			sum[l]=sum[n+1-l];
		}
	}
	// for(int i=0;i<=n;++i){
	// 	cout<<pre[i]<<" \n"[i==n];
	// }
	// for(int i=0;i<=n;++i){
	// 	cout<<sum[i]<<" \n"[i==n];
	// }
	ll ans=0;
	rep(l,1,n){
		ans=ans+sum[l]*qpow(l,mod-2,mod);
		ans%=mod;
	}
	printf("%lld\n",ans);
	return 0;
}
