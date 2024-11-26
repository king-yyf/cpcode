#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n), p(n), l(n + 1), r(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        p[a[i]] = i + 1;
    }

    l[0] = 1e9, r[0] = -1;
    for (int i = 1; i <= n; ++i) {
        r[i] = max(r[i - 1], p[i - 1]);
        l[i] = min(l[i - 1], p[i - 1]);
    }

    auto calc = [&](int m, int len) -> long long {
        if (m > n || len <= 0) return 0;
        if (m == 0) return 1ll * len  * (2 * n - len + 1) / 2;
        int y = n - r[m], x = l[m] - 1, k = r[m] - l[m] + 1;
        if (k > len) return 0;
        int left = len - k;
        x = min(x, left), y = min(y, left);
        int z = min(x, y) + 1;
        long long res = z * (z + 1ll) / 2;
        res += max(0ll, z * 1ll * (min(max(x, y), left) - z + 1));
        z = max(x, y);
        int num = min(x + y, left) - z;
        z = min(x, y);
        res += num * 1ll * (z - num + 1 + z) / 2;
        return res;
    };

    auto get = [&](int l1, int l2, int m1, int m2) {
        return calc(m1, l2) - calc(m1, l1 - 1) - calc(m2 + 1, l2) + calc(m2 + 1, l1 - 1);
    };

    for (int i = 0, l1, l2, m1, m2; i < q; ++i) {
        cin >> l1 >> l2 >> m1 >> m2;
        cout << get(l1, l2, m1, m2) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
