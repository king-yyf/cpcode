#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> x(n + 1), w(n + 1);
    vector<vector<long long>> dp(n + 1, vector<long long> (n + 1, -1e18));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) cin >> x[i];

    for (int i = 0, x, y; i < m; ++i) {
        cin >> x >> y;
        w[x] = y;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) 
            dp[i][j] = dp[i - 1][j - 1] + x[i] + w[j];
        dp[i][0] = 0;
        for (int j = 0; j < i; ++j)
            dp[i][0] = max(dp[i][0], dp[i - 1][j]);
    }

    cout << *max_element(dp[n].begin(), dp[n].end()) << "\n";
}