#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n;
	cin >> n;
	int L = 1, R = n;
	while (L < R ) {
		int m = (L + R) / 2;
		cout << "? 1 " << m << endl;
		int cnt = 0;
		for (int i = 1; i <= m; ++i) {
			int x;
			cin >> x;
			cnt += (x <= m);
		}
		if (cnt % 2 == 1) {
			R = m;
		} else {
			L = m + 1;
		}
	}
	cout << "! " << L << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}