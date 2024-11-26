#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), ans(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int l = (n - 1) / 2, r = l, cur = a[l];
    for (int k = n - 1; k >= 0; --k) {
        ans[k] = cur;
        if (l == 0 && r == n - 1) break;
        if (l + r == n - 1) {
            --l;
            cur = gcd(cur, a[l]);
        } else {
            ++r;
            cur = gcd(cur, a[r]);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i == n - 1];    
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
