#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll N=4e5+10; 
ll e[N],ne[N],h[N],idx,w[N],f[N],dp[N][2],fdp[N];
void add(int a,int b,int c){
	e[idx]=b;
	w[idx]=c;
	ne[idx]=h[a];
	h[a]=idx++;
}
void dfs1(ll u,ll t){
	for(ll i=h[u];i!=-1;i=ne[i]){
		ll x=e[i];
		if(x==t) continue;
		dfs1(x,u);
		ll d=fmax(1ll*f[x],dp[x][0])+w[i];
		if(d>=dp[u][0]){
			dp[u][1]=dp[u][0];
			dp[u][0]=d;
		}
		else if(d>dp[u][1]){
			dp[u][1]=d;
		}
	}
}
void dfs2(ll u,ll t){
	for(ll i=h[u];i!=-1;i=ne[i]){
		ll x=e[i];
		if(x==t) continue;
		ll d1=max(1ll*f[x],dp[x][0])+w[i];
		cout<<"u= "<<u-1<<", "<<f[x]<<" "<<dp[x][0]<<" "<<w[i]<<" " << x-1 <<"\n";
		cout<<"u= "<<u-1<<", x1="<<d1<<", v="<<x-1<<"\n";
		
		ll d2=d1==dp[u][0]?dp[u][1]:dp[u][0];
		// cout<<"u= "<<u-1<<", "<<d1<<", "<<d2<<"\n";
		fdp[x]=fmax(d2,fmax(f[u],fdp[u]))+w[i];
		dfs2(x,u);
	}
}
int main(){
	memset(h,-1,sizeof(h));
	ll n;
	cin>>n;
	for(int i=0;i<n-1;i++){
		ll a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	for(ll i=1;i<=n;i++){
		cin>>f[i];
	}
	dfs1(1,-1);
	dfs2(1,-1);
	// for(int i=1;i<=n;++i){
	// 	cout<<dp[i][0]<<" \n"[i==n];
	// }
	// for(int i=1;i<=n;++i){
	// 	cout<<dp[i][1]<<" \n"[i==n];
	// }
	// for(int i=1;i<=n;++i){
	// 	cout<<fdp[i]<<" \n"[i==n];
	// }
	// for(ll i=1;i<=n;i++) printf("%lld\n",max(dp[i][0],fdp[i]));
	return 0;
}