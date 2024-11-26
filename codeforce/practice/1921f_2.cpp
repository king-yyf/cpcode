#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using ll = long long;

const int B = 300;

void solve() {
	int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &x : a) {
    	cin >> x;
    }

    vector<array<int, 4>> qs(q);

    for (int i = 0; i < q; ++i) {
    	for (int j = 0; j < 3; ++j) {
    		cin >> qs[i][j];
    	}
    	qs[i][0]--;
    	qs[i][3] = i;
    }

    sort(qs.begin(), qs.end(), [&](auto &x, auto &y){
    	return x[1] < y[1];
    });

    vector<long long> s1(n), s2(n);
    int last = 0;

    auto get = [&](int d) {
    	last = d;
    	for (int i = n - 1; i >= 0; --i) {
    		s1[i] = s2[i] = a[i];
    		if (i + d < n) {
    			s1[i] += s1[i + d];
    			s2[i] += s2[i + d] + s1[i + d];
    		}
    	}

    };

    vector<long long> ans(q);
    for (auto &[s, d, k, id] : qs) {
    	long long c = 0;
    	if (d < B) {
    		if (last != d) get(d);
    		c = s2[s];
    		if (s + d * k < n) {
    			c -= s2[s + d * k];
    			c -= s1[s + d * k] * k;
    		}
    	} else {
    		for (int i = s, t = 1; t <= k; i += d, t++) 
    			c += t * 1ll * a[i];
    	}
    	ans[id] = c;
    }

    for (int i = 0; i < q; ++i) {
    	cout << ans[i] << " \n"[i == q - 1];
    }
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
