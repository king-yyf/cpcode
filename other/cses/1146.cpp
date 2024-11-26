#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    long long n;
    cin>>n;
    long long ans = 0;
    int x = 63 - __builtin_clzll(n);
    for (int i = 0; i <= x; i++){
        long long c = 1ll << i, cnt = 0;
        long long  p = (n + 1) / c;
        cnt = (p / 2) * c;
        long long  d = (n + 1) % c;
        if (p % 2 != 0) cnt += d;
        ans = (ans + cnt) ;
    }
    cout<<ans;

    return 0;
}
