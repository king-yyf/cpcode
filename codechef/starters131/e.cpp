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

char s[210000];

int main()
{
	int i,j,k,n,l,t,m,x,y,o,b1,base;
	_int64 ans,sum,toadd,tmp;
	map<int,int> mp;
	scanf("%d",&t);
	for (l=0;l<t;l++)
	{
		scanf("%d",&n);
		scanf("%s",s);
		base=0;
		mp.clear();
		toadd=0;ans=0;sum=0;
		for (i=0;i<n;i++)
		{
			mp[base]++;
			if (s[i]=='a')
				base++;
			else if (s[i]=='b') base--;
			if (s[i]=='b') sum+=(i+1);
			if (mp.find(base+1)!=mp.end())
			{
				tmp=mp[base+1];
				mp[base]+=tmp;
				mp.erase(base+1);
				sum-=tmp;
			}
			if (s[i]=='c')
			{
				toadd=sum;
			}
			//cerr<<"sum,toadd,ans:"<<sum<<" "<<toadd<<" "<<ans<<endl;
			ans+=toadd;
		}
		printf("%lld\n",ans);
	}
}