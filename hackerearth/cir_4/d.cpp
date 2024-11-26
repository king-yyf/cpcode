#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> xorSqeCnt(vector<int> &a) {
	int n = a.size(), k = 1025;
	vector<int> f(k), g(k), ans(n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < k; ++j) {
			int v = f[j];
			if (v) g[j] = g[j ^ a[i - 1]] = 1;
			g[a[i - 1]] = 1;
		}
		f.swap(g);
		g.assign(k, 0);
		for (int j = 0; j < k; ++j) if (f[j])
			ans[i - 1]++;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	auto ans = xorSqeCnt(a);
	for (int i = 0; i < n; ++i) {
		cout << ans[i] << " \n"[i == n - 1];
	}

	return 0;
}