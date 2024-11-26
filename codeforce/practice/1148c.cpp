#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> p(n), a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    	a[i]--;
    	p[a[i]] = i;
    }

    vector<array<int, 2>> ops;

    for (int i = 1; i < n / 2; ++i) {
    	if (a[i] == i) continue;
    	if (p[i] < n / 2) {
    		int t = p[i];
    		p[i] = n - 1;
    		p[a[n - 1]] = t;
    		swap(a[t], a[n - 1]);
    		ops.push_back({t, n - 1});
    		t = a[i];
    		swap(a[n - 1], a[i]);
    		ops.push_back({i, n - 1});
    		p[i] = i;
    		p[t] = n - 1;
    	} else {
    		int t = p[i];
    		ops.push_back({t, n - 1});
    		p[a[t]] = 0;
    		p[a[0]] = t;
    		swap(a[t], a[0]);

    		ops.push_back({0, n - 1});
    		p[a[0]] = n - 1;
    		p[a[n - 1]] = 0;
    		swap(a[0], a[n - 1]);

    		ops.push_back({i, n - 1});
    		p[a[i]] = n - 1;
    		p[a[n - 1]] = a[i];
    		swap(a[i], a[n - 1]);
    	}
    }

    for (int i = n / 2; i < n - 1; ++i) {
    	if (a[i] == i) continue;
    	if (p[i] < n / 2) {
    		int t = p[i];
    		ops.push_back({t, n - 1});
    		p[a[n - 1]] = t;
    		p[a[t]] = n - 1;
    		swap(a[t], a[n - 1]);

    		ops.push_back({0, n - 1});
    		p[a[0]] = n - 1;
    		p[a[n - 1]] = 0;
    		swap(a[0], a[n - 1]);

    		ops.push_back({0, i});
    		p[a[0]] = i;
    		p[a[i]] = 0;
    		swap(a[i], a[0]);

    	} else {
    		int t = p[i];
    		ops.push_back({t, 0});
    		p[a[t]] = 0;
    		p[a[0]] = t;
    		swap(a[t], a[0]);

    		ops.push_back({0, i});
    		p[a[i]] = 0;
    		p[a[0]] = i;
    		swap(a[0], a[i]);
    	}
    }

    if (a[n - 1] != n - 1) {
    	ops.push_back({n - 1, 0});
    	swap(a[0], a[n - 1]);
    }

    // for (int i = 0; i < n; ++i) {
    // 	cout << a[i] << " \n"[i == n - 1];
    // }

    cout << ops.size() << "\n";

    for (auto &[l, r] : ops) {
    	cout << l + 1 << " " << r + 1 << "\n";
    }

    return 0;
}
