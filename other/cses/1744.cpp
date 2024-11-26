#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1744

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    const int inf = 1e9;
    vector f(n + 1, vector<int>(m + 1, inf));
    for (int i = 0; i <= n; ++i) {
    	for (int j = 0; j <= m; ++j) {
    		if (i == j) f[i][j] = 0;
    		else {
    			for (int k = 1; k < i; ++k) 
    				f[i][j] = min(f[i][j], f[k][j] + f[i - k][j] + 1);
    			for (int k = 1; k < j; ++k)
    				f[i][j] = min(f[i][j], f[i][k] + f[i][j - k] + 1);
    		}
    	}
    }

    cout << f[n][m];

    return 0;
}
