#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m, ans = 0;
    cin >> n >> m;
    vector a(n, vector<int>(m)), f(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
        	cin >> a[i][j];
    }
    auto check = [&](int x) {
    	f[1][0] = 1;
    	for (int i = 0; i < n; ++i) {
    		for (int j = 0; j < m; ++j) {
    			f[i + 1][j + 1] = ((a[i][j] & x) == x && (f[i][j + 1] || f[i + 1][j]));
    		}
    	}
    	return f[n][m];
    };

    for (int i = 30; i >= 0; --i) {
    	if (check(ans | (1 << i)))
    		ans = ans | (1 << i);
    }

    cout << ans << '\n';

    return 0;
}
