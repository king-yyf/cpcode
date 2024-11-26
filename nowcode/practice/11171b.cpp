#include <bits/stdc++.h>
using namespace std;

int a[5005], f[5005][5005], n, m, l, r;
int main(){
    scanf("%d%d",&n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d",a + i);
    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i + l - 1 <= n; ++i) {
            int j = i + l - 1;
            f[i][j] = max({a[i] ^ a[j], f[i][j - 1], f[i + 1][j]});
        }
    }

    while(m--) {
        scanf("%d%d",&l,&r);
        printf("%d\n", f[l][r]);
    }
    return 0;
}
