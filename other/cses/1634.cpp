#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int coinChange(vector<int>& coins, int n) {
    vector<int> dp(n + 1, INT_MAX/2);
    dp[0] = 0;
    for (int i = 0; i <= n; ++i) {
        for (auto x : coins) 
            if (i >= x) 
                dp[i] = min(dp[i], dp[i - x] + 1);
    }
    return dp[n] == INT_MAX / 2 ? -1 : dp[n];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    cout << coinChange(a, x);
    return 0;
}
