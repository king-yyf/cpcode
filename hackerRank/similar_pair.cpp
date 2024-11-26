#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> a;
    FenwickTree(int n) : n(n), a(n) {}
    FenwickTree(vector<T> &A) : FenwickTree((int)A.size()) {
        for (int i = 0; i < n; ++i) add(i, A[i]);
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    T ask(int x) {
        T ans = 0;
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
    T ask(int l, int r) { //sum[l..r]
        if (l > r) return 0;
        return ask(r) - ask(l - 1);
    }
};


long long similarPair(int n, int k, vector<vector<int>> edges) {
	vector<vector<int>> g(n);
	vector<int> vis(n);
	for (auto &e: edges) {
		int x = e[0] - 1, y = e[1] - 1;
		g[x].push_back(y);
		vis[y] = 1;
	}
	int root = 0;
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) root = i;	
	}
	FenwickTree<int> t(n);
	long long ans = 0;
	function<void(int)> dfs = [&](int u) {
		int x = max(0, u - k), y = min(n - 1, u + k);
		ans += t.ask(x, y);
		t.add(u, 1);
		for (auto &v : g[u]) {
			dfs(v);
		}
		t.add(u, -1);
	};
	dfs(root);
	return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> es(n - 1,vector<int>(2));
    for (auto &e : es) {
    	cin >> e[0] >> e[1];
    }
    cout << similarPair(n, k, es);
    return 0;
}
