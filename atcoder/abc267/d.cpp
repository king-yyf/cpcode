#include <bits/stdc++.h>
using namespace std;

void solve(){
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	vector dp(n + 1, vector<long long>(m + 1, -1e18));

	for (int i = 0; i <= n; ++i)
		dp[i][0] = 0;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= min(i, m); ++j) {
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + j * a[i - 1]);
		}
 	}

 	cout << dp[n][m] << "\n";

}

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
	return 0;
}
