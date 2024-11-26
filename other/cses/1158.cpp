#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, x;
    cin >> n >> x;
    vector<int> p(n), w(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];	
    }
    for (int i = 0; i < n; ++i) {
        cin >> w[i];	
    }

    vector<int> f(x + 1);

    for (int i = 0; i < n; ++i) {
    	for (int j = x; j >= p[i]; --j) {
    		f[j] = max(f[j], f[j - p[i]] + w[i]);
    	}
    }

    cout << f[x] << '\n';

    return 0;
}
