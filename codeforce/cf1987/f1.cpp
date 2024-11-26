#include <bits/stdc++.h>
using namespace std;

void solve_() {
    int n;
    cin >> n;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        --a;
        ++c[a];
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, n));
    for (int k = 0; k <= n; ++k) {
        dp[n][k] = 0;
    }

    for (int i = n - 1; i >= 0; --i) {
        for (int k = 0; k < n; ++k) {
            if (c[i] == 0) {
                dp[i][k] = dp[i + 1][k];
                continue;
            }
            dp[i][k] = dp[i + 1][k + 1] + 1;
            if (k >= c[i]) {
                dp[i][k] = min(dp[i][k], dp[i + 1][k - c[i]]);
            }
        }
    }

    cout << dp[0][0] << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve_();
    }
    return 0;
}