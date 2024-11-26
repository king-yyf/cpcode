#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    const int mod = 1e9 + 7;
    
    int n;
    cin >> n;

    vector<int> f(n + 1);

    f[0] = 1;
    for (int  i = 0; i <= n; ++i) {
    	for (int x : {1, 2, 3, 4, 5, 6}) {
    		if (i >= x) {
    			f[i] = (f[i] + f[i - x]) % mod;
    		}
    	}
    }
    cout << f[n] << '\n';

    return 0;
}
