#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q, x, y;
    string s;
    cin >> n >> s >> q;

    int p = 0, m = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '+') p ++;
        else m++;
    }

    for (int k = 0; k < q; ++k) {
    	cin >> x >> y;
        if (p == m) {
            cout << "YES\n";
            continue;
        }
        if (x == y) {
            cout << "NO\n";
             continue;
        }
        long long t = (p - m) * 1ll * y / (y - x), d = (p - m) * 1ll * y % (y - x);
        if (d == 0 && -m <= t && t <= p) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}