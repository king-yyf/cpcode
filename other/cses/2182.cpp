#include <bits/stdc++.h>
using namespace std;


long long  qpow(long long m, long long k, long long p) {
    long long res = 1 % p, t = m;
    while (k) {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}

array<int, 3> divisor_cnt_sum_pro(vector<pair<int, int>> &a, int mod) {
	array<int, 3> c{1, 1, 1};
	int sq = 1, num = 1, d = 1, flag = 0;
	for (auto &[x, y] : a) {
		c[0] = (c[0] * (y + 1ll)) % mod;
		int gmum = (qpow(x, y + 1, mod) + mod - 1) * qpow(x - 1, mod - 2, mod) % mod;
		c[1] = c[1] * 1ll * gmum % mod;
		sq = sq * 1ll * qpow(x, y / 2, mod) % mod;
		num = num * 1ll * qpow(x, y, mod) % mod;
		if ((y & 1) && flag == 0) {
			d = d * ((y + 1ll) / 2) % (mod - 1);
			flag = 1;
		} else d = d * (y + 1ll) % (mod - 1);
	}
	c[2] = flag ?  qpow(num, d, mod) : qpow(sq, d, mod);
	return c;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, x, y;
    cin >> n;
    vector<pair<int,int> > a;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        a.emplace_back(x, y);	
    }
    const int mod = 1e9 + 7;
    auto ans = divisor_cnt_sum_pro(a, mod);
    cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << '\n';

    return 0;
}
