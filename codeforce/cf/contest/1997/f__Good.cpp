#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <random>
#include <chrono>
 
using namespace std;
 
#define _int64 long long
#define mo 998244353

int f[41];
int d[1001][55001];

int main()
{
	int i,j,k,n,l,t,m,x,y,o,b1,ma;
	int ans,cnt,rem;
	f[1]=1;
	f[2]=1;
	for (i=3;i<=40;i++)
		f[i]=f[i-1]+f[i-2];
	//cerr<<"f[10]:"<<f[10]<<" "<<f[40]<<endl;
	scanf("%d%d%d",&n,&x,&m);
	ma=0;
	memset(d,0,sizeof(d));
	d[n][0]=1;
	for (i=1;i<=x;i++)
	{
		ma=n*f[i];
		for (j=n;j>0;j--)
			for (k=0;k<=ma;k++)
			{
				d[j-1][k+f[i]]+=d[j][k];
				d[j-1][k+f[i]]%=mo;
			}
	}
	ans=0;
	for (i=0;i<=n*f[x];i++)
	{
		cnt=0;
		rem=i;
		for (j=40;j>=1;j--)
		{
			if (rem>=f[j])
			{
				rem-=f[j];
				cnt++;
			}
		}
		//cerr<<"i,cnt,m:"<<i<<" "<<cnt<<" "<<m<<" "<<d[0][i]<<endl;
		if (cnt==m)
		{
			ans+=d[0][i];
			ans%=mo;
		}
	}
	printf("%d\n",ans);
}