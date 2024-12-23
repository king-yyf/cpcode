#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC optimize("no-stack-protector,fast-math")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef vector<string> vs;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<pdd> vpdd;
typedef vector<vd> vvd;
#define yn(ans) printf("%s\n", (ans)?"Yes":"No");
#define YN(ans) printf("%s\n", (ans)?"YES":"NO");
template<class T> bool chmax(T &a, T b) {
	if (a >= b) return false;
	a = b; return true;
}
template<class T> bool chmin(T &a, T b) {
	if (a <= b) return false;
	a = b; return true;
}
#define FOR(i, s, e, t) for ((i) = (s); (i) < (e); (i) += (t)) 
#define REP(i, e) for (int i = 0; i < (e); ++i) 
#define REP1(i, s, e) for (int i = (s); i < (e); ++i)
#define RREP(i, e) for (int i = (e); i >= 0; --i)
#define RREP1(i, e, s) for (int i = (e); i >= (s); --i)
#define all(v) v.begin(), v.end()
#define pb push_back
#define qb pop_back
#define pf push_front
#define qf pop_front
#define maxe max_element
#define mine min_element
ll inf = 1e18;
#define DEBUG printf("%d\n", __LINE__); fflush(stdout);
template<class T> void print(vector<T> &v, bool withSize = false) {
	if (withSize) cout << v.size() << endl;
	REP(i, v.size()) cout << v[i] << " "; 
	cout << endl;
}
mt19937_64 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

int __FAST_IO__ = []() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	return 0;
}();

class SuffixArray {
public:
    using size_type = unsigned;
    using pointer = size_type*;
    using const_pointer = const size_type*;
    const_pointer sa, rk, ht;

private:
    std::unique_ptr<size_type[]> data;

private:
    template<typename S>
    inline static bool substring_equal(const S& s, size_type p1, size_type p2, size_type len) {
        for (size_type i = 0;i < len;++i)
            if (s[p1 + i] != s[p2 + i])
                return false;
        return true;
    }

    template<typename S>
    inline static void induced_sort(
        const S& s,
        pointer sa,
        bool* type,
        pointer pos,
        pointer lbuk,
        pointer sbuk,
        size_type n,
        size_type m,
        size_type n0) {
        std::fill_n(sa, n, 0);
        lbuk[0] = 0;
        for (size_type i = 1;i < m;++i)
            lbuk[i] = sbuk[i - 1];
        for (size_type i = n0;i-- > 0;)
            sa[--sbuk[s[pos[i]]]] = pos[i];
        sbuk[m - 1] = n;
        for (size_type i = 1;i < m;++i)
            sbuk[i - 1] = lbuk[i];
        sa[lbuk[s[n - 1]]++] = n - 1;
        for (size_type i = 0;i < n;++i)
            if (sa[i] > 0 && !type[sa[i] - 1])
                sa[lbuk[s[sa[i] - 1]]++] = sa[i] - 1;
        lbuk[0] = 0;
        for (size_type i = 1;i < m;++i)
            lbuk[i] = sbuk[i - 1];
        for (size_type i = n;i-- > 0;)
            if (sa[i] > 0 && type[sa[i] - 1])
                sa[--sbuk[s[sa[i] - 1]]] = sa[i] - 1;
    }

    template<typename S>
    static void sais(
        const S& s,
        pointer sa,
        bool* type,
        pointer len,
        pointer pos,
        pointer lbuk,
        pointer sbuk,
        size_type n,
        size_type m) {
        type[n - 1] = false;
        for (size_type i = n - 1;i-- > 0;)
            type[i] = s[i] != s[i + 1] ? s[i] < s[i + 1] : type[i + 1];
        size_type n0 = 0;
        for (size_type i = 1;i < n;++i)
            if (!type[i - 1] && type[i])
                pos[n0++] = i;
        std::fill_n(len, n, 0);
        for (size_type p = n - 1, i = n0;i-- > 0;p = pos[i])
            len[pos[i]] = p - pos[i] + 1;
        std::fill_n(sbuk, m, 0);
        for (size_type i = 0;i < n;++i)
            ++sbuk[s[i]];
        for (size_type i = 1;i < m;++i)
            sbuk[i] += sbuk[i - 1];
        induced_sort(s, sa, type, pos, lbuk, sbuk, n, m, n0);
        sbuk[m - 1] = n;
        for (size_type i = 1;i < m;++i)
            sbuk[i - 1] = lbuk[i];
        size_type m0 = -1;
        size_type ppos = -1, plen = 0;
        for (size_type i = 0;i < n;++i) {
            if (len[sa[i]] == 0) continue;
            if (len[sa[i]] != plen || !substring_equal(s, sa[i], ppos, plen)) ++m0;
            plen = len[sa[i]];
            len[sa[i]] = m0;
            ppos = sa[i];
        }
        const pointer s0 = sa;
        const pointer sa0 = sa + n0;
        for (size_type i = 0;i < n0;++i)
            s0[i] = len[pos[i]];
        if (++m0 < n0)
            sais(s0, sa0, type + n, len, pos + n0, lbuk, lbuk + n0, n0, m0);
        else for (size_type i = 0;i < n0;++i)
            sa0[s0[i]] = i;
        for (size_type i = 0;i < n0;++i)
            pos[i + n0] = pos[sa0[i]];
        induced_sort(s, sa, type, pos + n0, lbuk, sbuk, n, m, n0);
    }

public:
    template<typename S>
    SuffixArray(const S& s, size_type n, size_type m)
        : data(std::make_unique<size_type[]>(3 * n)) {
        const auto type = std::make_unique<bool[]>(2 * n);
        const auto lbuk = std::make_unique<size_type[]>(std::max(n, m));
        const auto sbuk = std::make_unique<size_type[]>(m);
        const pointer sa = data.get(), rk = sa + n, ht = rk + n;
        sais(s, sa, type.get(), rk, ht, lbuk.get(), sbuk.get(), n, m);
        for (size_type i = 0;i < n;++i)
            rk[sa[i]] = i;
        for (size_type k = 0, i = 0;i < n;++i) {
            if (rk[i] == 0) continue;
            if (k > 0) --k;
            for (size_type j = sa[rk[i] - 1], l = n - std::max(i, j);k < l;++k)
                if (s[i + k] != s[j + k]) break;
            ht[rk[i]] = k;
        }
        this->sa = sa;
        this->rk = rk;
        this->ht = ht;
    }

    inline size_type suffix(size_type p) const {
        return sa[p];
    }

    inline size_type rank(size_type p) const {
        return rk[p];
    }

    // height start from 1
    inline size_type height(size_type p) const {
        return ht[p];
    }
};

template <typename T> struct Discrete {
	Discrete() {}
	Discrete(vector<T> &v): p(v) {init();}
	void add(T t) {
		p.pb(t);
	}
	
	void init() {
		sort(all(p));
		p.resize(unique(all(p)) - p.begin());
	}
	
	int size() {return p.size();}
	
	int id(T t) {
		return lower_bound(all(p), t) - p.begin();
	}
	
	T operator[](int id) {return p[id];}
 
    	vector<T> &get() {return p;}
	vector<T> p;
};

int main() {
    int N;
    cin >> N;
    
    vi v(N);
    Discrete<int> d;
    REP(i, N) cin >> v[i], d.add(v[i]);
    d.init();
    vi v2(N);
    REP(i, N) v2[i] = d.id(v[i]);
    SuffixArray sa(v2, N, N);
    
    vi b(N + 1, 0), pre(N + 1, 0);
    REP(i, N) {
    	b[i + 1] = b[i] ^ (v[i] & 1);
    	pre[i + 1] = pre[i] + b[i + 1];
    }
    
    ll ans = 0;
    REP(i, N) {
    	int s = sa.suffix(i);
        // cout << s << ' ';
    	int l = i == 0 ? s : s + sa.height(i);
        cout << l << ' ';
    	if (b[s]) {
    		ans += pre[N] - pre[l];
    	} else {
    		ans += (N - l) - (pre[N] - pre[l]);
    	}
    }
    cout << '\n';
    printf("%lld\n", ans);
    return 0;
}