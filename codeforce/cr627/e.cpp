#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, h, l, r;
    cin >> n >> h >> l >> r;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    const int inf = 1e9;
    vector f(n+1, vector<int>(h+1, -inf));
    f[0][0] = 0;

    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j < h; ++j) {
    		int x = (a[i] + j) % h, y = (a[i] + j - 1) % h;
    		f[i + 1][x] = max(f[i + 1][x], f[i][j] + (x >= l && x <= r));
    		f[i + 1][y] = max(f[i + 1][y], f[i][j] + (y >= l && y <= r));
    	}
    }
    int ans = 0;
    for (int i = 0; i < h; ++i)
    	ans = max(ans, f[n][i]);
    cout << ans << "\n";

    return 0;
}
