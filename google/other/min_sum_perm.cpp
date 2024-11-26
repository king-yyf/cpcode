#include<bits/stdc++.h>
using namespace std;

long long minSumPerm(vector<int> &a, int k) {
    int n = a.size();
    vector dp(k + 1, vector<long long>(k + 1));
    vector<long long> diff(n);
    long long p1 = n / k, p2 = p1 + 1, n1 = 0, n2 = 0;

    for (int i = 1; i <= k; ++i) {
        long long t = (n - i) / k + 1;
        if (t == p1) n1++;
        if (t == p2) n2++;
    }

    sort(a.begin(), a.end());

    for (int i = 1; i < n; ++i) {
        diff[i] = diff[i - 1] + abs(a[i] - a[i - 1]);
    }

    auto get = [&](int x, int y) {
        return abs(diff[y - 1] - diff[x - 1]);
    };

    for (int i = 1; i <= n1; ++i) {
        int x = i * p1, y = x - p1 + 1;
        dp[i][0] = dp[i - 1][0] + get(y, x);
    }

    for (int i = 1; i <= n2; ++i) {
        int x = i * p2, y = x - p2 + 1;
        dp[0][i] = dp[0][i - 1] + get(y, x);
    }

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            long long s = i * p1 + j * p2;
            dp[i][j] = min(dp[i][j - 1] + get(s - p2 + 1, s), dp[i - 1][j] + get(s - p1 + 1, s));
        }
    }
    return dp[n1][n2];
}



int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
	cout << minSumPerm(a,k)<<"\n";
}