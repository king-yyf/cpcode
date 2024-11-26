#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
link: https://www.codechef.com/problems/RUMBLING
rating: 2009
*/

void solve() {
	int n, X, Y;
	string s;
	cin >> n >> s >> X >> Y;
	vector<long long> p(n + 1), g(n + 1);

	auto idx = [&](char ch) -> int {
		if (ch == 'S') return 0;
		else if (ch == 'W') return 1;
		else if (ch == 'N') return 2;
		return 3;
	};

	auto get = [&](char ch) -> pair<ll, ll> {
		int t = idx(ch);
		auto x = min(X * 1ll * (3 - t), Y * 1ll * (1 + t));
		long long y1, y2;
		y1 = t > 1 ? (5ll - t) * X : (1ll - t) * X;
		y2 = t > 1 ? (t - 1ll) * Y : (3ll + t) * Y;
		return {x, min(y1, y2)};
	};

	for (int i = 0; i < n; ++i) {
		auto [x, y] = get(s[i]);
		p[i + 1] = p[i] + x;
		g[i + 1] = g[i] + y;
	}

	long long ans = 1e18;

	for (int i = 0; i <= n; ++i) {
		long long cur = p[i] + g[n] - g[i];
		ans = min(ans, cur);
	}
	cout << ans << '\n';
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
