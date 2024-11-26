#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
	int n;
	cin >> n;
	vector<pair<int,int> > p(n);
	for (int i = 0; i < n; ++i) {
	     cin >> p[i].first;	
	}
	for (int i = 0; i < n; ++i) {
	     cin >> p[i].second;
	}
	sort(p.begin(), p.end());

	int ans = 0, x = 0;
	for (int i = 0; i < n; ++i) {
		if (p[i].first > x) {
			ans ++;
			x = p[i].second;
		} else {
			x = min(x, p[i].second);
		}
	}
	cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--) {
    	solve();
    }

    return 0;
}
