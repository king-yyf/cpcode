#include <bits/stdc++.h>
using namespace std;

using ll = long long;

long long  qpow(long long m, long long k, long long p) {
    long long res = 1 % p, t = m;
    while (k) {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}

long long sum_dovisors(long long n, int p) {
	long long ans = 0, z = qpow(2, p - 2, p);
	auto calc =  [&](long long l, long long r, long long mul) -> long long  {
		long long res = ((r * (r + 1) - l * (l + 1)) % p + p) % p;
		res = (res * z) % p;
		return res * mul;
	};
	for (int  i = 1; i * 1ll * i <= n; ++i) {
		long long r = n / i, l = n / (i + 1);
		ans = (ans + calc(l % p, r % p, i)) % p;
		if (i != n / i) {
			ans = (ans + (n / i) * i) % p;
		}
	}
	return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    long long n;
    cin >> n;
    const int mod = 1e9 + 7;
    cout << sum_dovisors(n, mod) << '\n';

    return 0;
}
