#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
https://www.codechef.com/problems/REMSUBARR
*/


void solve() {
	int n;
	cin >> n;
	vector<int> a(n), p(n);

	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		a[i]--;
		p[a[i]] = i;
	}

	int l = p[n - 1], r = p[n - 1], ans = 1;

	for (int i = n - 1; i >= 1; --i) {
		int x = p[i];
		l = min(l, x);
		r = max(r, x);
		if (r - l + 1 == n - i) {
			ans = r - l + 1;
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
