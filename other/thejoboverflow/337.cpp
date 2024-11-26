#include <bits/stdc++.h>
using namespace std;

// http://www.thejoboverflow.com/problem/337/

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define f3(i,a,b) for (int i=(a);i<(b);i++)
#define r3(i,b,a) for (int i=(b)-1;i>=(a);i--)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))

int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size(); s.assign(n + 1, 0); 
    for(int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];  
};
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 1e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

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
    template <class T> map<T, int> factorize(T x) const {
        map<T, int> ret;
        for (const auto &p : primes) {
            if (x < T(N + 1)) break;
            while (!(x % p)) x /= p, ret[p]++;
        }
        if (x >= T(N + 1)) ret[x]++, x = 1;
        while (x > 1) ret[min_fact[x]]++, x /= min_fact[x];
        return ret;
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


template<const unsigned &MOD>
struct _m_uint {
    unsigned val;
    _m_uint(int64_t v = 0) {
        if (v < 0) v = v % MOD + MOD; if (v >= MOD) v %= MOD;
        val = unsigned(v);
    }
    _m_uint(uint64_t v) { if (v >= MOD) v %= MOD; val = unsigned(v);}
    _m_uint(int v) : _m_uint(int64_t(v)) {}
    _m_uint(unsigned v) : _m_uint(uint64_t(v)) {}
    explicit operator uint64_t() const { return val; }
    _m_uint& operator+=(const _m_uint &other) {
        val = val < MOD - other.val ? val + other.val : val - (MOD - other.val);
        return *this;
    }
    static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
        return unsigned(x % m);
#endif
        unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }
    _m_uint& operator*=(const _m_uint &other) {
        val = fast_mod(uint64_t(val) * other.val);
        return *this;
    }
    _m_uint& operator/=(const _m_uint &other) { return *this *= other.inv();}
    friend _m_uint operator+(const _m_uint &a, const _m_uint &b) { return _m_uint(a) += b; }
    friend _m_uint operator*(const _m_uint &a, const _m_uint &b) { return _m_uint(a) *= b; }
    friend _m_uint operator/(const _m_uint &a, const _m_uint &b) { return _m_uint(a) /= b; }
    friend bool operator==(const _m_uint &a, const _m_uint &b) { return a.val == b.val; }
    static const int SAVE_INV = int(1e6) + 5;
    static _m_uint save_inv[SAVE_INV];
    static void prepare_inv() { // assert( is_prime(MOD) )
        for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1)
            assert(MOD % p != 0);
        save_inv[0] = 0, save_inv[1] = 1;
        for (int i = 2; i < SAVE_INV; i++)
            save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
    }
    _m_uint inv() const {
        if (save_inv[1] == 0) prepare_inv();
        if (val < SAVE_INV) return save_inv[val];
        _m_uint product = 1;
        unsigned v = val;
        do {
            product *= MOD - MOD / v;
            v = MOD % v;
        } while (v >= SAVE_INV);
        return product * save_inv[v];
    }
};

template<const unsigned &MOD> _m_uint<MOD> _m_uint<MOD>::save_inv[_m_uint<MOD>::SAVE_INV];

uint64_t random_address() { char *p = new char; delete p; return uint64_t(p); }
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));

extern const unsigned HASH_P = unsigned(-13337); // both P and (P - 1) / 2 are prime.
using hash_int = _m_uint<HASH_P>;

const uint64_t HASH_P2 = uint64_t(HASH_P) * HASH_P;
const int HASH_COUNT = 2;

uniform_int_distribution<unsigned> MULT_DIST(unsigned(0.1 * HASH_P), unsigned(0.9 * HASH_P));
const hash_int HASH_MULT[] = {MULT_DIST(rng), MULT_DIST(rng)};
const hash_int HASH_INV[] = {1 / HASH_MULT[0], 1 / HASH_MULT[1]};
vector<hash_int> hash_pow[] = {{1}, {1}};

template<typename T_string = string>
struct string_hash {
    // TODO: decide whether BUILD_REVERSE = true is needed.
    static const bool BUILD_REVERSE = true;

    static uint64_t hash(const T_string &str) {
        uint64_t result = 0;
        for (int h = 0; h < HASH_COUNT; h++) {
            uint64_t value = 1;
            for (const auto &x : str) value = (uint64_t(HASH_MULT[h]) * value + x) % HASH_P;
            result += value << (32 * h);
        }
        return result;
    }
    T_string str;
    vector<hash_int> _prefix[HASH_COUNT], _inv_prefix[HASH_COUNT];

    string_hash() { build({});}
    string_hash(const T_string &_str) { build(_str);}
    int length() const { return int(_prefix[0].size()) - 1;}
    template<typename T_char>
    void add_char(const T_char &c) {
        str.push_back(c);

        for (int h = 0; h < HASH_COUNT; h++) {
            _prefix[h].push_back(HASH_MULT[h] * _prefix[h].back() + c);

            if (hash_pow[h].size() < _prefix[h].size())
                hash_pow[h].push_back(HASH_MULT[h] * hash_pow[h].back());

            if (BUILD_REVERSE)
                _inv_prefix[h].push_back((_inv_prefix[h].back() + c) * HASH_INV[h]);
        }
    }
    void pop_char() {
        str.pop_back();
        for (int h = 0; h < HASH_COUNT; h++) {
            _prefix[h].pop_back();
            if (BUILD_REVERSE) _inv_prefix[h].pop_back();
        }
    }

    void build(const T_string &_str) {
        str = {}; str.reserve(_str.size());
        for (int h = 0; h < HASH_COUNT; h++) {
            hash_pow[h].reserve(_str.size() + 1);
            _prefix[h] = {0};
            _prefix[h].reserve(_str.size() + 1);

            if (BUILD_REVERSE) {
                _inv_prefix[h] = {0};
                _inv_prefix[h].reserve(_str.size() + 1);
            }
        }
        for (auto &c : _str) add_char(c);
    }

    uint64_t _single_hash(int h, int start, int end) const {
        uint64_t power = uint64_t(hash_pow[h][end - start]);
        return (power + uint64_t(_prefix[h][end]) + HASH_P2 - uint64_t(_prefix[h][start]) * power) % HASH_P;
    }

    uint64_t substring_hash(int start, int end) const {
        assert(0 <= start && start <= end && end <= length());
        return _single_hash(0, start, end) + (HASH_COUNT > 1 ? _single_hash(1, start, end) << 32 : 0);
    }

    uint64_t complete_hash() const { return substring_hash(0, length());}

    uint64_t _reverse_single_hash(int h, int start, int end) const {
        uint64_t power = uint64_t(hash_pow[h][end - start]);
        return (power + uint64_t(_inv_prefix[h][end]) * power + HASH_P - uint64_t(_inv_prefix[h][start])) % HASH_P;
    }

    uint64_t reverse_substring_hash(int start, int end) const {
        assert(0 <= start && start <= end && end <= length());
        return _reverse_single_hash(0, start, end) + (HASH_COUNT > 1 ? _reverse_single_hash(1, start, end) << 32 : 0);
    }

    uint64_t reverse_complete_hash() const { return reverse_substring_hash(0, length());}

    bool equal(int start1, int start2, int length) const {
        return substring_hash(start1, start1 + length) == substring_hash(start2, start2 + length);
    }

    bool is_palindrome(int start, int end) const {
        return substring_hash(start, end) == reverse_substring_hash(start, end);
    }
};

uint64_t concat_hashes(uint64_t hash1, uint64_t hash2, int len2) {
    if (len2 == 0) return hash1;
    uint64_t hash1_low = hash1 & unsigned(-1), hash2_low = hash2 & unsigned(-1);
    uint64_t power = uint64_t(hash_pow[0][len2]);
    uint64_t combined = (hash1_low * power + hash2_low + HASH_P - power) % HASH_P;
    if (HASH_COUNT > 1) {
        hash1 >>= 32, hash2 >>= 32;
        power = uint64_t(hash_pow[1][len2]);
        combined += (hash1 * power + hash2 + HASH_P - power) % HASH_P << 32;
    }
    return combined;
}



void ac_yyf(int tt) {
    rd(s);
    n=sz(s);
    Sieve p(N);
    string t=s;
    rev(t);
    string_hash f(s);
    string_hash g(t);

    vector<int> v{1};

    for(auto&x:p.primes){
    	if(x>n)break;
    	v.push_back(x);
    }
    for(auto&x:v){
    	if(n%x==0){
    		int j=0;
    		for(;j<n;j+=x){
    			auto a=f.substring_hash(j,j+x);
    			auto b=g.reverse_substring_hash(j,j+x);

    			if(a!=b) {break;}
    		}
    		if(j>=n) {
    			wt(x,nl);
    			return;
    		}
    	}
    }
    wt(-1,nl);
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
