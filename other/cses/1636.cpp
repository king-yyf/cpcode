#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1636

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, x;
    const int mod = 1e9 + 7;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    vector<int> f(x + 1);
    f[0] = 1;

    for (int c : a) {
        for (int i = c; i <= x; ++i) {
            f[i] = (f[i - c] + f[i]) % mod;
        }
    }

    cout << f[x] << '\n';

    return 0;
}
