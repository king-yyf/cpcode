#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/remainder-twist-987a698c/

void solve() {
	int n, r;
	cin >> n >> r;
	vector<long long> a(n);

	for (int i = 1; i <= n; ++i) {
		int x = n / i, y = n % i;
		if (y == i - 1) {
			a[0] += x;
			if (i < n) a[i] -= x;
		} else {
			a[0] += x;
			a[y + 1] -= x;
			a[y + 1] += x - 1;
			if (i < n) a[i] -= x - 1;
		}
 		if (i >= 1) a[1] += 1;
 		if (i < n) a[i] -= 1;
	}

	for (int i = 1; i < n; ++i)
		a[i] += a[i - 1];

	long long s = 0;
	int ans = -1;
	for (int i = n - 1; i >= 0; --i) {
		s += a[i];
		if (s >= r) {
			ans = i;
			break;
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
