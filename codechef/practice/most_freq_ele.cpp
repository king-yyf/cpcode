#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    vector<int> l(n), r(n);

    for (int i = n - 1; i >= 0; --i) {
    	if (i == n - 1 || a[i] != a[i + 1]) {
    		r[i] = i;
    	} else r[i] = r[i + 1];
    }

    for (int i = 0; i < n; ++i) {
    	if (i == 0 || a[i] != a[i - 1]) {
    		l[i] = i;
    	} else {
    		l[i] = l[i - 1];
    	}
    }

    for (int i = 0; i < q; ++i) {
    	int x, y, k;
    	cin >> x >> y >> k;
    	x--, y--;
    	int md = (x + y) / 2;
    	int cnt = min(y, r[md]) - max(x, l[md]) + 1;
    	cout << (cnt >= k ? a[md] : -1) << "\n"; 
    }

    return 0;
}
