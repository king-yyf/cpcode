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
 
using namespace std;
 
#define _int64 long long
#define mo 1000000007

int main()
{
    int i,j,k,n,x,y,l,t,m,o,p,b1,now,si;
    int ans[2][2];
    scanf("%d",&t);
    for (l=0;l<t;l++)
    {
        scanf("%d",&n);
        memset(ans,0,sizeof(ans));
        now=0;
        si=0;
        for (i=1;;i++)
        {
            if (now+i>=n)
            {
                if (now%2==0)
                {
                    x=(n-now+1)/2;
                    y=(n-now)/2;
                }
                else
                {
                    x=(n-now)/2;
                    y=(n-now+1)/2;
                }
                ans[si][0]+=x;
                ans[si][1]+=y;
                break;
            }
            else
            {
                if (now%2==0)
                {
                    x=(i+1)/2;
                    y=i/2;
                }
                else
                {
                    x=i/2;
                    y=(i+1)/2;
                }
                ans[si][0]+=x;
                ans[si][1]+=y;
                now+=i;
                if ((i%4==1)||(i%4==3))
                    si=1-si;
            }
            
        }
        for (i=0;i<2;i++)
            printf("%d ",ans[i][0]+ans[i][1]);
            //for (j=0;j<2;j++)
              //  printf("%d ",ans[i][j]);
        printf("\n");
    }
	return 0;
}

