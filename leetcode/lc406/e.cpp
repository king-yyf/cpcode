#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
struct data
{
    int v , flag;
    bool operator<(const data &a)const {return v > a.v;}
}a[20010];
int cnt[2];
int main()
{
    int n , m , i;
    ll ans = 0;
    scanf("%d%d" , &n , &m) , n -- , m -- ;
    for(i = 1 ; i <= n ; i ++ ) scanf("%d" , &a[i].v);
    for(i = 1 ; i <= m ; i ++ ) scanf("%d" , &a[i + n].v) , a[i + n].flag = 1;
    sort(a + 1 , a + n + m + 1);
    for(i = 1 ; i <= n + m ; i ++ ) ans += (ll)a[i].v * (cnt[a[i].flag ^ 1] + 1) , cnt[a[i].flag] ++ ;
    printf("%lld\n" , ans);
    return 0;
}
 