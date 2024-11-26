#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.eolymp.com/en/problems/7261

const int N = 2020;

double d[N][N];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(16);
    
    int n, m;

    cin >> n >> m;

    d[0][n] = 1;

    for (int i = 1; i <= n; ++i) {
    	for (int j = n - i; j <= n + i; ++j) {
    		d[i][j] = (d[i - 1][j - 1] + d[i - 1][j + 1]) / 2;
    	}
    }

    cout << d[n][n + m] << '\n';

    return 0;
}

