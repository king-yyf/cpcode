#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<long long> suf(n + 1), res(n);
    for (int i = n - 1; i >= 0; --i) {
        suf[i] = suf[i + 1] + a[i];
    }

    res[(n + 1) / 2] = suf[n / 2];

    long long cur = 0;
    for (int i = 0; i < n; ++i) {
        if ((n - i) & 1) {
            cur += a[i];
            res[(n - 1 - i) / 2] = cur + suf[n - (n - 1 - i) / 2];
        }
    }

    for (int i = 0, x; i < q; ++i) {
        cin >> x;
        int l = 0, r = (n + 1) / 2;
        while (l < r) {
            int md = (l + r + 1) / 2;
            if (a[n - md] - x < x - a[n - md * 2 + 1]) {
                r = md - 1;
            } else l = md;
        }
        cout << res[l] << '\n';
    }

    return 0;
}
