#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m, x;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> x;
        a[i + 1] = a[i] ^ x;	
    }

    for (int i = 0, x, y; i < m; ++i) {
    	cin >> x >> y;
    	cout << (a[y] ^ a[x - 1]) << '\n';
    }

    return 0;
}
