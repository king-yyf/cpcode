#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    const int inf = 1e9;

    vector<int> f(n + 1, inf);

    f[0] = 0;
    for (int i = 1; i <= n; ++i) {
    	string s = to_string(i);
        for (char c : s) {
            f[i] = min(f[i], f[i - c + '0'] + 1);
        }
    }

	cout << f[n] << '\n';

    return 0;
}
