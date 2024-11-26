#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1620

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, t;
    cin >> n >> t;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    long long l = 0, r = 1e18, ans = r;

    auto chk = [&](ll x) {
    	ll c = 0;
    	for (int i = 0; i < n; ++i) {
    		c += (x / a[i]);
    		if (c >= t) return 1;
    	}
    	return 0;
    };

    while (l <= r) {
    	ll md = (l + r) / 2;
    	if (chk(md)) {
    		ans = md;
    		r = md - 1;
    	} else l = md + 1;
    }

    cout << ans << '\n';

    return 0;
}
