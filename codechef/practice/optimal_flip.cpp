#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
https://www.codechef.com/problems/OPTMFLP18
*/


void solve() {
	int n;
	cin >> n;
	vector<int> a(n);

	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	a.push_back(0);

	int cnt = 0;
	vector<int> p;
	for (int i = 0; i <= n; ++i) {
		if (a[i] & 1) {
			cnt ++;
		} else {
			if (cnt > 0) p.push_back(cnt);
			cnt = 0;
		}
	}
	if (p.size() == 0) {
		cout << n * 1ll * (n + 1) / 2 << "\n";
		return;
	}
	
	sort(p.begin(), p.end());
	int x = p.back();
	p.pop_back();
	p.push_back(x / 2);
	if (x - x / 2 - 1 > 0)
	p.push_back(x - x / 2 - 1);

	long long ans = 0;
	for (int x : p) {
		ans += x * 1ll * (x + 1) / 2;
	}

	cout << n * 1ll * (n + 1) / 2 - ans << "\n";
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
