#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-1093

using ll = long long;

const int mod = 1e9 + 7;

long long  qpow(long long m, long long k, long long p) {
    long long res = 1 % p, t = m;
    while (k) {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    int s = n * (n + 1) / 2;

    if (s & 1) {
    	cout << 0 << '\n';
    	return 0;
    }

    vector<int> dp(s + 1);

    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
    	for (int j = s; j >= i; --j) {
    		dp[j] = (dp[j] + dp[j - i]) % mod;
    	}
    }

    int ans = dp[s / 2];

    ans = (ans * qpow(2, mod - 2, mod)) % mod; 

    cout << ans << '\n';

    return 0;
}
