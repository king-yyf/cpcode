#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://codeforces.com/contest/1715/problem/D

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;

    vector<int> f(n, (1 << 30) - 1);
    vector<vector<pair<int,int>> > g(n); 

    int l, r, x;
    for (int i = 0; i < q; ++i) {
    	cin >> l >> r >> x;
    	l--, r--;
    	f[l] &= x;
    	f[r] &= x;
    	g[l].emplace_back(r, x);
    	g[r].emplace_back(l, x);
    }

    for (int i = 0; i < n; ++i) {
    	int t = 0;
    	for (auto [j, x] : g[i]) {
    		t |= x & ~f[j];
    		if (j == i) {
    			t = x;
    		}
    	}
    	f[i] = t;
    	cout << f[i] << " \n"[i == n - 1];
    }

    return 0;
}
