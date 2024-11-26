#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int f[20][1<<10][1<<10],lg[20];
int cnt;ll l,r;
inline bool check(int x,int y)
{
	for(int i=0;i<10;++i)
		if((x&(1<<i)) && ((i&1)==((y>>i)&1)))
				return false;
	return true;
}
inline ll dp(int limit,int lzero,int dep,int sta1,int sta2)
{
	if(dep==0)return check(sta1,sta2);
	else if(!limit && !lzero && f[dep][sta1][sta2]!=-1)return f[dep][sta1][sta2];
	else
	{
		ll ret=0;
		int i,nxt=limit?lg[dep]:9;
		for(i=0;i<=nxt;++i)
			ret+=dp(limit&&(i==nxt),lzero&&(i==0),dep-1,(lzero&&(i==0))?0:(sta1|(1<<i)),(lzero&&(i==0))?0:(sta2^(1<<i)));
		if(!limit && !lzero)f[dep][sta1][sta2]=ret;
		return ret;
	}
}
inline ll solve(ll x)
{
	cnt=0;while(x)
	{
		lg[++cnt]=x%10;
		x/=10;
	}
	return dp(1,1,cnt,0,0);
}
int main()
{
	memset(f,-1,sizeof f);
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%lld %lld",&l,&r);
		printf("%lld %lld\n",solve(r),solve(l-1));
	}
	return 0;
}

// 8373369810, 14394392869