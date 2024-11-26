#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a (n + 2);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    long long ans = n * 1ll * (n + 1) / 2;
    for (int i = 1; i <= n; ++i) {
        ans += (a[i] != a[i + 1]) * i * 1ll * (n - i);
    }
    while (m--) {
        int i, x;
        cin >> i >> x;
        ans -=  (a[i] != a[i + 1]) * i * 1ll * (n - i);
        ans -=  (a[i] != a[i - 1]) * (i - 1) * 1ll * (n - i + 1);
        a[i] = x;
        ans +=  (a[i] != a[i + 1]) * i * 1ll * (n - i);
        ans +=  (a[i] != a[i - 1]) * (i - 1) * 1ll * (n - i + 1);
        cout << ans << '\n';
    }
   
    return 0;
}
