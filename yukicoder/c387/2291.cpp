#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
ゆきこちゃん设定了一个由0到9这10种数字组成的W位密码，但她忘记了。
于是她通过H次查询得到了关于密码的提示。
每次查询得到的回复是一个由37种字符（从0到9的数字，从a到z的字母，?）组成的W字符的字符串。
第i次（1 ≤ i ≤ H）查询的回复记为Q，第i次查询的第j个（1 ≤ j ≤ W）字符记为Qij。
Qij分别具有以下信息：

如果Qij是从0到9的数字，表示密码的第j位是该数字。
如果Qij是从a到z的字母，表示在第一次查询的回复中，对于Qij = Qik的k，密码的第j位和第k位是相同的数字。
如果Qij是?，表示在第i次查询的回复中没有提供关于密码第j位的信息。
在第i（1 ≤ i ≤ H）行接收到第一次查询的回复时，输出作为密码可能的组合数 mod 998244353。注意，第i次查询的信息继承了满足j<i的第j次查询的信息。
*/

struct DSU {
    vector<int> p, siz;
    DSU(int n) : p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
    bool same(int x, int y) { return get(x) == get(y); }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
    int size(int x) { return siz[get(x)]; }
    vector<vector<int>> groups() {
        vector<vector<int>> res(p.size());
        for (int i = 0; i < p.size(); i++) res[get(i)].push_back(i);
        res.erase(
            remove_if(res.begin(), res.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            res.end());
        return res;
    }
};

ll inverse(ll a, ll m) { 
    a %= m; if (a == 0) return 0; if (a < 0) a += m;
    ll u = 0, v = 1;
    while (a) { ll t = m / a;  m -= t * a; swap(a, m); u -= t * v; swap(u, v); }
    return u;
}
template <int m, bool is_prime = true>
struct static_mod {
    using mint = static_mod;
    static constexpr int mod() { return m; }
    static_mod() : _v(0) {}
    template <class T> static_mod(T v) {ll x = (ll)(v % (ll)(umod())); if (x < 0) x += umod(); _v = (unsigned int)(x);}
    static_mod(unsigned int v) { _v = (unsigned int)(v % umod());}
    unsigned int val() const { return _v; }
    mint& operator++() { _v++; if (_v == umod()) _v = 0; return *this;}
    mint& operator--() { if (_v == 0) _v = umod(); _v--; return *this;}
    mint operator++(int) { mint result = *this; ++*this; return result;}
    mint operator--(int) { mint result = *this; --*this; return result;}
    mint& operator+=(const mint& rhs) { _v += rhs._v; if (_v >= umod()) _v -= umod();return *this;}
    mint& operator-=(const mint& rhs) { _v -= rhs._v; if (_v >= umod()) _v += umod();return *this;}
    mint& operator*=(const mint& rhs) { unsigned long long z = _v; z *= rhs._v; _v = (unsigned int)(z % umod()); return *this;}
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(ll n) const {mint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x;n >>= 1;} return r;}
    mint inv() const { if(is_prime) {assert(_v);return pow(umod() - 2);} return inverse(_v, m);}
    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs;}
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs;}
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs;}
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v;}
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v;}
    friend ostream& operator << (ostream& out, const mint& n) { return out << n.val(); }
    friend istream& operator >> (istream& in, mint& n) { ll x; in >> x; n = mint(x); return in; }
private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
};
using mint = static_mod<998244353>; // 1000000007

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;

    vector<int> c(n, -1);

    string s;
    DSU d(n);
    int cnt = 0, siz = n, tot = 0;
    for (int i = 0; i < q; ++i) {
    	cin >> s;
    	vector<int> p(26, -1);
    	for (int j = 0; j < n; ++j) {
    		if (s[j] >= '0' && s[j] <= '9') {
    			int x = s[j] - '0', u = d.get(j);
    			if (c[u] != -1) {
    				if (c[u] != x) cnt = -1;
    			} else {
    				c[u] = x;
    				tot++;
    			}
    		} else if (s[j] != '?') {
    			int x = s[j] - 'a';
    			if (p[x] == -1) p[x] = j;
    			else {
    				int u = d.get(p[x]), v = d.get(j);
    				if (c[u] != -1) {
    					if (c[v] != -1) {
    						if (c[u] != c[v]) {
    							cnt = -1;
    						} else {
    							if (!d.same(u, v)) {
    								siz--;
    								tot--;
    								d.merge(u, v);
    							}
    							c[d.get(u)] = c[u];
    						}
    					} else  {
    						siz--;
    						d.merge(u, v);
    						c[d.get(u)] = c[u];
    					}
    				} else {
    					if (c[v] != -1) {
    						siz--;
    						d.merge(u, v);
    						c[d.get(u)] = c[v];
    					} else {
    						if (!d.same(u, v)) {
								siz--;
								d.merge(u, v);
							}
    					}
    				}
    			}
    		}
    	}
    	// cout<<"tot="<<tot<<", siz="<<siz<<"\n";
    	cout << (cnt < 0 ? 0 : mint(10).pow(siz - tot)) << '\n';
    }

    return 0;
}
