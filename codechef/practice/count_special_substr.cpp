#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.codechef.com/problems/BDGFT

void solve() {
	string s;
	cin >> s;
	int n = s.size();

	vector<int> p(n + 1);
	for (int i = 0; i < n; ++i) {
		p[i + 1] = p[i] + (s[i] == '1');
	}

	long long ans = 0;
	for (int i = 1; ;i++) {
		int x = i * i + i;
		if (x > n) break;
		for (int j = 0; j + x <= n; ++j) {
			int cnt1 = p[j + x] - p[j];
			if (cnt1 == i) ans++;
		}
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
