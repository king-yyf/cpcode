#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, x;
    cin >> n >> m;
    vector<long long> s(n + 1);

    for (int i = 0; i < n; ++i) {
        cin >> s[i + 1];
        s[i + 1] += s[i];
    }

    long long sum = s[n];

    for (int i = 0; i < n; ++i) {
        s[i + 1] = max(s[i + 1], s[i]);
    }

    for (int i = 0; i < m; ++i) {
        cin >> x;
        if (sum <= 0 && s[n] < x) {
            cout << "-1" << " \n"[i == m - 1];
        } else {
            int t = x <= s[n] ? 0 : (x - s[n] + sum - 1) / sum, pos = lower_bound(s.begin(), s.end(), x - t * sum) - s.begin() - 1;
            cout << pos + t * 1ll * n<< " \n"[i == m - 1];
        } 
    }   
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
