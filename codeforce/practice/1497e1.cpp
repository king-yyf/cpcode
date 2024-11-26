#include <bits/stdc++.h>
using namespace std;

struct Sieve {
    vector<int> min_fact, primes;
    int N;
    Sieve(int n): N(n), min_fact(n + 1) {
        for (int d = 2; d <= N; d++) {
            if (!min_fact[d]) {
                min_fact[d] = d;
                primes.push_back(d);
            }
            for (const auto &p : primes) {
                if (p > min_fact[d] or d * 1ll * p > N) break;
                min_fact[d * p] = p;
            }
        }
    }
    bool is_prime(int x) {
        if (x < N + 1) return min_fact[x] == x;
        assert(N * 1ll * N >= x);
        for (const auto &p : primes) if (x % p == 0) return false;
        return true;
    }
    template<class T> T factorize(T x) const {
    	T ans = 1;
        int cnt = 0, last = 0;
		while (x > 1) {
		    int p = min_fact[x];
		    if (last == p) {
		        ++cnt;
		    } else {
		        if (cnt & 1) ans *= last;
		        last = p, cnt = 1;
		    }
		    x /= p;
		}
		if (cnt % 2 == 1) ans *= last;
        return ans;
    }
    template <class T> vector<T> divisors(T x) const {
        vector<T> ret{1};
        for (const auto p : factorize(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                for (T a = 1, d = 1; d <= p.second; d++) {
                    a *= p.first;
                    ret.push_back(ret[i] * a);
                }
            }
        }
        // sort(ret.begin(), ret.end()); // if need sort
        return ret; 
    }
    template <class T> map<T, T> euler_of_divisors(T x) const {
        assert(x >= 1);
        map<T, T> ret; ret[1] = 1;
        vector<T> divs{1};
        for (auto p : factorize(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                ret[divs[i] * p.first] = ret[divs[i]] * (p.first - 1);
                divs.push_back(divs[i] * p.first);
                for (T a = divs[i] * p.first, d = 1; d < p.second; a *= p.first, d++) {
                    ret[a * p.first] = ret[a] * p.first;
                    divs.push_back(a * p.first);
                }
            }
        }
        return ret;
    }
    vector<int> moebius_table() const {
        vector<int> ret(N + 1);
        for (unsigned i = 1; i <= N; i++) {
            if (i == 1) ret[i] = 1;
            else if ((i / min_fact[i]) % min_fact[i] == 0) ret[i] = 0;
            else ret[i] = -ret[i / min_fact[i]];
        }
        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    Sieve s(1e7);
    int t;
    cin >> t;
    while (t--) {
    	int n, x, ans = 1; 
		cin >> n >> x;
		unordered_map<int, int> mp;
		for (int i = 0, l = 0; i < n; ++i) {
		    cin >> x;
		    x = s.factorize(x);
		    if (mp.count(x) && mp[x] >= l) {
                ans++;
                l = i;
            }
            mp[x] = i;
		}
        cout << ans << '\n';
    }

    return 0;
}
