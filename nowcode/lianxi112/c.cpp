#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
const int N = 1e6+10;

int a[N], h[N], b[N], tt = 0;

int lengthOfLIS() {
    memset(h, 0x3f, sizeof h);
    for (int i = 0; i < tt; ++i) {
        *lower_bound(h, h + tt, b[i]) = b[i];
    }
    return lower_bound(h, h + tt, 0x3f3f3f3f) - h;;
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int n, x;
    ll ans=0;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) {
        scanf("%d", &x); a[x] = i + 1;
    }
    for (int i = 0; i < n; i ++ ) {
        scanf("%d", &x);
        if (a[x]) b[tt++] = a[x];
    }
    ans = lengthOfLIS();
    printf("%lld\n",n-ans);
    return 0;
}