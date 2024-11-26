#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    const int mod = 1e9 + 7;
    vector<int> f(n + 1, 1), g(n + 1);
    f[0] = 1;
    for (int i = 0; i < n; ++i) {
    	if (a[0][i] == '*') f[i + 1] = 0;
    	else f[i + 1] = f[i];
    }

    for (int i = 1; i < n; ++i) {
    	for (int j = 0; j < n; ++j) {
    		if (a[i][j] == '*') {
    			g[j + 1] = 0;
    		} else {
    			g[j + 1] = (g[j] + f[j + 1]) % mod;
    		}
    	}
    	f.swap(g);
    	g.assign(n + 1, 0);
    }
    cout << f[n] << '\n';

    return 0;
}
