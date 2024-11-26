#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector f(k + 1, vector<int> (k + 1));
    f[0][0] = 1;
    auto g = f;
    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j <= k; ++j) {
    		for (int l = 0; l <= k; ++l) {
    			g[j][l] = f[j][l];
    			if (j >= a[i]) g[j][l] |= f[j - a[i]][l];
    			if (j >= a[i] && l >= a[i]) g[j][l] |= f[j - a[i]][l- a[i]];
    		}
    	}
    	g.swap(f);
    }

    vector<int> res;
    for (int i = 0; i <= k; ++i) {
    	if (f[k][i]) res.push_back(i);
    }
    cout << res.size() << '\n';
    for (int x : res) {
    	cout << x << ' ';
    }

    return 0;
}