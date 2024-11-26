#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
	    cin >> a[i];	
	}
	map<int, int> mp;
	for (int x : a) {
		mp[x] ++;
	}

	int m = 1e9;
	for (auto &[k, v] : mp) {
		m = min(m, v);
	}
	
	int ans = n;
	for (int i = 1; i <= m; ++i) {
		int cnt = 0, o = 1;
		for (auto &[k, v] : mp) {
			int t = (v - 1) / (i + 1) + 1;
			cnt += t;
			if (i * t > v) {
				o = 0;
				break;
			}
		}
		if (o && cnt < ans) ans = cnt;
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
