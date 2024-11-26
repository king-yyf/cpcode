#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    if ((n + m - 1) % 2 != 0) {
        cout << "NO\n";
        return;
    }
    const int inf = 1e9;
    
    vector mn(n, vector<int>(m, inf)), mx(n, vector<int>(m, -inf));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                mn[i][j] = mx[i][j] = 0;
            } else if (i == 0) {
                mn[i][j] = mn[i][j - 1];
                mx[i][j] = mx[i][j - 1];
            } else if (j == 0) {
                mn[i][j] = mn[i - 1][j];
                mx[i][j] = mx[i - 1][j];
            } else {
                mn[i][j] = min(mn[i - 1][j], mn[i][j - 1]);
                mx[i][j] = max(mx[i - 1][j], mx[i][j - 1]);
            }
            mn[i][j] += a[i][j];
            mx[i][j] += a[i][j];
        }
    }
    
    if (mn[n - 1][m - 1] <= 0 && mx[n - 1][m - 1] >= 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
