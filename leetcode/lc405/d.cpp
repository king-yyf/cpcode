#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

using ll = long long;
#define ar(x) array<int,x> 
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
// mt19937 mrand(random_device{}()); 
// int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> T f_div(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0));}
template <class T> T c_div(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0));}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template <typename T, typename U> // pair
ostream& operator<<(ostream& out, const pair<T, U>& a) {return out << a.first << ' ' << a.second;}
template <typename T>  // vector
ostream& operator<<(ostream& out, const vector<T>& a) {for(int i=0,n=a.size(); i<n; ++i) out<<a[i]<<" \n"[i==n-1]; return out;}
template <typename T, size_t N> // array
ostream& operator<<(ostream& out, const array<T, N>& a) {for(int i=0;i<N;++i)cout<<a[i]<<" \n"[i==N-1];return out;}
template <typename T, typename U> // pair
istream& operator>>(istream& in, pair<T, U>& a) {return in >> a.first >> a.second;}
template <typename T> // vector
istream& operator>>(istream& in, vector<T>& a) {for (auto &x: a) in >> x; return in;}
template <typename T, size_t N> // array
istream& operator>>(istream& in, array<T, N>& a) {for (int i=0;i<N;++i) in >> a[i]; return in;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
#ifdef sigma-yyf
#define dbg(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
template <class H, class... Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {
    cerr << s << ": " << h, ((cerr << ", " << t), ..., (cerr << "\n"));
}
#else
#define dbg(...) void(0)
#endif
template<class Fun> class Y_comb {
    Fun _f;
public:
    template<class T> explicit Y_comb(T &&fun): _f(forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...As) {return _f(ref(*this), forward<Args>(As)...);}
};
template<class Fun> decltype(auto) y_comb(Fun &&fun) { return Y_comb<decay_t<Fun>>(forward<Fun>(fun));}

struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;
constexpr char nl = '\n';
constexpr int inf = 1'061'109'567;
constexpr ll infll = 2'000'000'000'000'000'000;
constexpr int N = 2e5 + 5;
int n, m, k;

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
        for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1) assert(MOD % p != 0);
        save_inv[0] = 0, save_inv[1] = 1;
        for (int i = 2; i < SAVE_INV; i++) save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
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
mt19937_64 rng_hash(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
extern const unsigned HASH_P = unsigned(-13337); // both P and (P - 1) / 2 are prime.
using hash_int = _m_uint<HASH_P>;
const uint64_t HASH_P2 = uint64_t(HASH_P) * HASH_P;
const int HASH_COUNT = 2;
const int INF = int(1e9) + 5;
uniform_int_distribution<unsigned> MULT_DIST(unsigned(0.1 * HASH_P), unsigned(0.9 * HASH_P));
const hash_int HASH_MULT[] = {MULT_DIST(rng_hash), MULT_DIST(rng_hash)};
const hash_int HASH_INV[] = {1 / HASH_MULT[0], 1 / HASH_MULT[1]};
vector<hash_int> hash_pow[] = {{1}, {1}};

template<typename T_string = string>
struct string_hash {
    static const bool BUILD_REVERSE = false; // if need BUILD_REVERSE, set true
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
    bool is_palindrome(int start, int end) const { // assert(BUILD_REVERSE = true)
        return substring_hash(start, end) == reverse_substring_hash(start, end);
    }
    int compare(int start1, int start2, int max_length = INF) const;
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
template<typename T_string>
int first_mismatch(const string_hash<T_string> &hash1, int start1,
                   const string_hash<T_string> &hash2, int start2, int max_len = INF) {
    max_len = min({max_len, hash1.length() - start1, hash2.length() - start2});
    static const int FIRST = 5;
    int first = min(max_len, FIRST);
    for (int i = 0; i < first; i++)
        if (hash1.str[start1 + i] != hash2.str[start2 + i]) return i;
    if (hash1.substring_hash(start1, start1 + max_len) == hash2.substring_hash(start2, start2 + max_len))
        return max_len;
    static const int MANUAL = 15;
    int low = first, high = max_len - 1;
    while (high - low > MANUAL) {
        int mid = (low + high + 1) / 2;
        if (hash1.substring_hash(start1, start1 + mid) == hash2.substring_hash(start2, start2 + mid))
            low = mid;
        else
            high = mid - 1;
    }
    for (int i = low; i < high; i++)
        if (hash1.str[start1 + i] != hash2.str[start2 + i]) return i;
    return high;
}
template<typename T_string>
int hash_compare(const string_hash<T_string> &hash1, int start1,
                 const string_hash<T_string> &hash2, int start2, int max_len = INF) {
    int mismatch = first_mismatch(hash1, start1, hash2, start2, max_len);
    int len1 = min(hash1.length() - start1, max_len), len2 = min(hash2.length() - start2, max_len);
    if (mismatch == min(len1, len2))
        return len1 == len2 ? 0 : (len1 < len2 ? -1 : +1);
    if (hash1.str[start1 + mismatch] == hash2.str[start2 + mismatch])
        return 0;
    return hash1.str[start1 + mismatch] < hash2.str[start2 + mismatch] ? -1 : +1;
}
template<typename T_string>
int string_hash<T_string>::compare(int start1, int start2, int max_len) const {
    return hash_compare(*this, start1, *this, start2, max_len);
}

template<typename T>
struct ST {
    int n = 0;
    vector<vector<T>> mat;
    static int largest_bit(int x) { return 31 - __builtin_clz(x);}
    ST(const vector<T> &a = {}) { if (!a.empty()) build(a);}
    void build(const vector<T> &a) {
        n = int(a.size());
        int max_log = largest_bit(n) + 1;
        mat.resize(max_log);
        for (int k = 0; k < max_log; k++)
            mat[k].resize(n - (1 << k) + 1);
        if (n > 0) mat[0] = a;

        for (int k = 1; k < max_log; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                mat[k][i] = min(mat[k - 1][i], mat[k - 1][i + (1 << (k - 1))]);
    }
    T get_val(int a, int b) const {
        assert(0 <= a && a < b && b <= n);
        int t = largest_bit(b - a);
        return min(mat[t][a], mat[t][b - (1 << t)]);
    }
};
template <class T = int, bool build_lcp = false> 
struct SA {
    int n = -1;
    vector<int> sa, rnk, lcp, s2;
    ST<int> st;
    SA(): n(0) {}
    SA(const vector<T>& s) : n(s.size()), s2(n) {
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
        int now = 0;
        for (int i = 0; i < n; ++i) {
            if (i && s[idx[i - 1]] != s[idx[i]]) now++;
            s2[idx[i]] = now;
        }
        get_suffix_array(s2, now);
        if (build_lcp) lcp_array(s2);
    }
    SA(const string& s) : n(s.size()), s2(n){
        for (int i = 0; i < n; ++i) s2[i] = s[i];
        get_suffix_array(s2, 255);
        if (build_lcp) lcp_array(s2);
    }
    void get_suffix_array(vector<int>& s, int upper) {
        assert(0 <= upper);
        for (int d : s) assert(0 <= d && d <= upper);
        sa = sa_is(s, upper);
    }
    vector<int> sa_naive(const vector<int>& s) {
        int n = int(s.size());
        vector<int> sa(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int l, int r) {
            if (l == r) return false;
            while (l < n && r < n) {
                if (s[l] != s[r]) return s[l] < s[r];
                l++, r++;
            }
            return l == n;
        });
        return sa;
    }
    vector<int> sa_doubling(const vector<int>& s) {
        int n = int(s.size());
        vector<int> sa(n), rnk = s, tmp(n);
        iota(sa.begin(), sa.end(), 0);
        for (int k = 1; k < n; k *= 2) {
            auto cmp = [&](int x, int y) {
                if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
                int rx = x + k < n ? rnk[x + k] : -1, ry = y + k < n ? rnk[y + k] : -1;
                return rx < ry;
            };
            sort(sa.begin(), sa.end(), cmp);
            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++) 
                tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            swap(tmp, rnk);
        }
        return sa;
    }

    template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
    vector<int> sa_is(const vector<int>& s, int upper) {
        int n = int(s.size());
        if (n == 0) return {}; if (n == 1) return {0};
        if (n == 2) { if (s[0] < s[1]) return {0, 1}; else return {1, 0};}
        if (n < THRESHOLD_NAIVE) return sa_naive(s);
        if (n < THRESHOLD_DOUBLING) return sa_doubling(s);
        vector<int> sa(n), sum_l(upper + 1), sum_s(upper + 1);
        vector<bool> ls(n);
        for (int i = n - 2; i >= 0; i--) 
            ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
        for (int i = 0; i < n; i++) {
            if (!ls[i]) sum_s[s[i]]++;
            else sum_l[s[i] + 1]++;
        }
        for (int i = 0; i <= upper; i++) {
            sum_s[i] += sum_l[i];
            if (i < upper) sum_l[i + 1] += sum_s[i];
        }

        auto induce = [&](const vector<int>& lms) {
            fill(sa.begin(), sa.end(), -1);
            vector<int> buf(upper + 1);
            copy(sum_s.begin(), sum_s.end(), buf.begin());
            for (auto d : lms) {
                if (d == n) continue;
                sa[buf[s[d]]++] = d;
            }
            copy(sum_l.begin(), sum_l.end(), buf.begin());
            sa[buf[s[n - 1]]++] = n - 1;
            for (int i = 0; i < n; i++) {
                int v = sa[i];
                if (v >= 1 && !ls[v - 1]) sa[buf[s[v - 1]]++] = v - 1;
            }
            copy(sum_l.begin(), sum_l.end(), buf.begin());
            for (int i = n - 1; i >= 0; i--) {
                int v = sa[i];
                if (v >= 1 && ls[v - 1]) sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        };

        vector<int> lms_map(n + 1, -1), lms;
        int m = 0;
        for (int i = 1; i < n; i++) {
            if (!ls[i - 1] && ls[i])  lms_map[i] = m++;
        }
        lms.reserve(m);
        for (int i = 1; i < n; i++) if (!ls[i - 1] && ls[i]) lms.push_back(i);
        induce(lms);
        if (m) {
            vector<int> sorted_lms, rec_s(m);
            sorted_lms.reserve(m);
            for (int v : sa) 
                 if (lms_map[v] != -1) sorted_lms.push_back(v);
            int rec_upper = 0;
            rec_s[lms_map[sorted_lms[0]]] = 0;
            for (int i = 1; i < m; i++) {
                int l = sorted_lms[i - 1], r = sorted_lms[i];
                int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
                int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
                bool same = true;
                if (end_l - l != end_r - r) same = false;
                else {
                    while (l < end_l) {
                        if (s[l] != s[r]) break;
                        l++, r++;
                    }
                    if (l == n || s[l] != s[r]) same = false;
                }
                if (!same) rec_upper++;
                rec_s[lms_map[sorted_lms[i]]] = rec_upper;
            }

            auto rec_sa = sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

            for (int i = 0; i < m; i++) 
                sorted_lms[i] = lms[rec_sa[i]];
            induce(sorted_lms);
        }
        return sa;
    }
    void get_rnk() {rnk.resize(n); for(int i = 0; i < n; ++i) rnk[sa[i]] = i;}
    void lcp_array(vector<T>& s) {
        assert(n >= 1);
        get_rnk();
        lcp.assign(n - 1, 0);
        int h = 0;
        for (int i = 0; i < n; ++i) {
            if (h > 0) h--;
            if (rnk[i] == 0) continue;
            int j = sa[rnk[i] - 1];
            for (; j + h < n && i + h < n; h++) 
                if (s[j + h] != s[i + h]) break;
            lcp[rnk[i] - 1] = h;
        }
    }
    bool contains(const string& s) { // 是否包含子串s O(mlog(n))
        int m = s.size();
        auto cmp = [&](int x) {
            for (int j = 0; x + j < n and j < m; ++j) {
                if (s2[x + j] < s[j]) return -1;
                if (s2[x + j] > s[j]) return 1;
            }
            return n - x < m ? -1 : 0; 
        };
        int l = 0, r = n - 1;
        while (l <= r) {
            int md = (l + r) / 2;
            int c = cmp(sa[md]);
            if (c == 0) return true;
            else if (c < 0)  l = md + 1;
            else r = md - 1;
        }
        return false;
    }
    int count(const string& s) { // s作为子串的出现次数 O(mlog(n))
        int m = s.size();
        if (n < m) return 0;
        auto lower = [&](int h) {
            for (int j = 0; h + j < n and j < m; j++) {
                if (s2[h + j] < s[j]) return true;
                if (s2[h + j] > s[j]) return false;
            }
            return n - h < m;
        };
        auto upper = [&](int h) {
            for (int j = 0; h + j < n and j < m; j++) 
                if (s2[h + j] > s[j]) return false;
            return true;
        };
        const auto L = partition_point(sa.begin(), sa.end(), lower);
        const auto R = partition_point(L, sa.end(), upper);
        return distance(L, R);
        // return vector<int>(L, R); // 如果需要返回出现的位置
    }
    long long distinct_substr() const { // 不同子串的数目, assert(build_lcp = True)
        long long res = n * (n + 1ll) / 2;
        for (int x : lcp) 
            res -= x;
        return res;
    }
    //返回s,t的最长公共子串<s中的下标，长度>，传入 s+'#'+t，m为s.size()
    pair<int, int> longest_common_substr(int m) { // assert(build_lcp = True)
        int len = 0, idx = 0;
        for (int i = 0; i < n - 1; ++i) {
            if ((sa[i] < m) != (sa[i + 1] < m) && lcp[i] > len) 
                len = lcp[i], idx = sa[i];
        }
        return {idx, len};
    }
    void build_rmq() {vector<int> a(n);for(int i=1; i<n; ++i) a[i]=lcp[i-1]; st.build(a);} 
    int get_lcp_from_ranks(int a, int b) const { //保证build_rmq已执行
        if (a == b) return n - sa[a];
        if (a > b) swap(a, b);
        return st.get_val(a + 1, b + 1);
    }
    int get_lcp(int a, int b) const { //s[a:n-1],s[b:n-1]的最长公共前缀
        if (a >= n || b >= n) return 0;
        if (a == b) return n - a;
        return get_lcp_from_ranks(rnk[a], rnk[b]);
    }
    int comp(int a, int b, int len = -1) const { //O(1)时间比较s[a:a+len-1],s[b:b+len-1]
        if (len < 0) len = n; if (a == b) return 0;
        int k = get_lcp(a, b); if (k >= len) return 0;
        if (a + k >= n || b + k >= n) return a + k >= n ? -1 : 1;
        return s2[a + k] < s2[b + k] ? -1 : (s2[a + k] == s2[b + k] ? 0 : 1);
    }
    void sort_substrs(vector<array<int, 2>> &qs) { // a[i]: s[l..r-1]
        sort(qs.begin(), qs.end(), [&](array<int, 2> &a, array<int, 2> &b){
            int n1 = a[1] - a[0], n2 = b[1] - b[0], cmp = comp(a[0], b[0], min(n1, n2));
            if (cmp != 0) return cmp < 0;
            return n1 != n2 ? n1 < n2 : (a < b);
        });
    }
    long long count_borders() const { // assert(build_lcp = True)
        long long ans = (n + 1ll) * n / 2, s = 0;
        vector<pair<int,int>> sk;
        for (int i = 1; i < n; ++i) {
            int len = lcp[i - 1], cnt = 1;
            while (!sk.empty() && len <= sk.back().first) {
                s -= sk.back().first * 1ll * sk.back().second;
                cnt += sk.back().second;
                sk.pop_back();
            }
            sk.emplace_back(len, cnt);
            s += len * 1ll * cnt;
            ans += s;
        }
        return ans;
    }
};



class Solution {
public:
    int minimumCost(string s, vector<string>& w, vector<int>& c) {
        map<uint64_t,int> mp;
        n=sz(s),m=sz(c);
        SA<int> sa(s);

        auto dfs1 = y_comb([&](auto dfs, int l, int r) -> int {
            
        });
        dfs1(0, n);

        f0(m){
            if(!sa.contains(w[i]))continue;
            string_hash f(w[i]);
            auto h=f.complete_hash();
            if(mp.count(h)){
                mp[h]=min(mp[h],c[i]);
            }else{
                mp[h]=c[i];
            }
        }

    }
};

#ifdef sigma-yyf
int main(){
    vector<int> v,a,b;
    string s,t;
    vector<string> sv;
    vector<vector<int>> vv;
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    // Solution so;
    // rd(a,k);
    // auto ans = so.;
    // wt(ans);
    cout<<'\n';
    return 0;
}
#endif