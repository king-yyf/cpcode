#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/horse-race-122f4ccc/


void solve() {
	int n,m,k;
	cin >> n >> m >> k;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
	    cin>>a[i];	
	}
	vector<int> b(m);
	for (int i = 0; i < n; ++i) {
		if (a[i] <= m) {
			b[a[i] - 1] ++;
		}
	}

	int l = 1, r = n, ans = l;
	while (l <= r) {
		int md = (l + r) / 2;
		if (md * m > n) {
			r = md - 1;
			continue;
		}

		int t = 0;
		for (int i = 0; i < m; ++i) {
			t += max(md - b[i], 0);
		}

		if (t <= k) {
			ans = md;
			l = md + 1;
		} else r = md - 1;

	}
	cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin>>t;
    while(t--){
    	solve();
    }

    return 0;
}
