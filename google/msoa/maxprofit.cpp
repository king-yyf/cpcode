#include<bits/stdc++.h>
using namespace std;

long long maxProfit(vector<int> &a, vector<int> &b) {
    int n = a.size(), m = b.size();
    vector<long long> p(n + 1);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + a[i];
    }
    vector dp(n + 1, vector<long long>((1 << m), -1));
    long long inf = 1e18, ans = 0;

    function<long long(int, int)> dfs = [&](int i, int mask) {
        if (i >= n) {
            return mask > 0 ? -inf : 0;
        }
        long long &ans = dp[i][mask];
        if (ans != -1) return ans;
        ans = dfs(i + 1, mask);
        for (int k = 0; k < m; ++k) {
            if (mask & (1 << k)) {
                long long val = p[i + b[k]] - p[i];
                ans = max(ans, val + dfs(i + b[k], mask ^ (1 << k)));
            }
        }
        return ans;
    };

    dfs(0, (1 << m) - 1);
    for (int i = 0; i < (1 << m); ++i) 
    	for (int j = 0; j < n; ++j)
    	ans = max(ans, dp[j][i]);

    return ans;
}

long long maxProfit1(vector<int> &a, vector<int> &b) {
    int n = a.size(), m = b.size();
    vector<long long> p(n + 1);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + a[i];
    }
    vector dp(n + 1, vector<long long>((1 << m), -1));
    long long inf = 1e18, ans = 0;

    function<long long(int, int)> dfs = [&](int i, int mask) -> long long {
        if (i >= n) return 0;
        if (dp[i][mask] >= 0) return dp[i][mask];
        dp[i][mask] = 0;
        for (int k = 0; k < m; ++k) {
            if (!(mask & (1 << k))) {
                dp[i][mask] = max(dp[i][mask], p[i + b[k]] - p[i] + dfs(i + b[k], mask | (1 << k)));
            }
        }
        return dp[i][mask] = max(dp[i][mask], dfs(i + 1, mask));
    };

    return dfs(0, 0);;
}

int main(){
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
	cout << fixed << setprecision(10);
	int n, m;
	cin >> n >> m;
	vector<int> a(n),b(m);
	for(int i = 0; i < n; ++i) cin >> a[i];
		for(int i = 0; i < m; ++i) cin >> b[i];
			cout << maxProfit1(a, b) << "\n";
}