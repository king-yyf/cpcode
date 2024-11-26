#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    auto p = a;
    p.push_back(0);

    vector<int> f(n + 1, -1);
    if (a[0] > 0) f[0] = 0;

    for (int i = 1; i < n; ++i) {
        if (f[i - 1] == -1) continue;
        if (a[i] > 0) f[i] = f[i - 1];
        else {
            int x = i, cur = f[i - 1];
            while (a[x] == 0) {
                if (x == 0) {
                    cur = -1;
                    break;
                }
                a[x]++;
                cur++;
                x /= 2;
                a[x]--;
            }
            f[i] = cur;
        }
    }
    for (int i = 0; i <= n; ++i) {
        if (i == 0) cout << p[0] << ' ';
        else {
            cout << (f[i - 1] == -1 ? -1 : f[i - 1] + p[i]) << " \n"[i == n];
        }
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
