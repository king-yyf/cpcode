#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-2413

using ll = long long;
const int M = 1e9 + 7, N = 1e6 + 2;
long long dp[N][2];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    dp[1][0] = dp[1][1] = 1;
    for (int i = 2; i < N; ++i) {
    	dp[i][0] = (dp[i - 1][0] * 4 + dp[i - 1][1]) % M;
    	dp[i][1] = (dp[i - 1][0] + dp[i - 1][1] * 2) % M;
    }

    int t, n;
    cin >> t;
    while (t--) {
    	cin >> n;
    	cout << (dp[n][0] + dp[n][1]) % M << '\n';
    }
    return 0;
}
