#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
	int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i];	
        a[i]--, b[i]--;
        g[b[i]].push_back(a[i]);
    }
    vector<int> d(n, -1);
    vector<int> q{0};
    d[0] = 0;
    for (int i = 0; i < q.size(); ++i) {
    	int x = q[i];
    	for (auto &v : g[x]) {
    		if (d[v] == - 1) {
    			d[v] = d[x] + 1;
    			q.push_back(v);
    		}
    	}
    }

    if (q.size() < n) {
    	cout << "INFINITE\n";
    	return;
    }
    cout << "FINITE\n";

    vector<vector<int>> f(n);
    for (int i = 0; i < q.size(); ++i) {
    	for (int j = 0; j <= d[q[i]]; ++j) {
    		f[j].push_back(q[i]);
    	}
    }

    vector<int> ans;
    for (int i = 0; i < n; ++i) {
    	ans.insert(ans.end(), f[i].rbegin(), f[i].rend());
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] + 1 << " \n"[i == ans.size() - 1];
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
