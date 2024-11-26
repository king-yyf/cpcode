#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

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
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
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
template<class A> void dbg(A x) { cout<<x<<' ';}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

template <typename ...Types>
using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;
template <typename ReturnType, typename Callable, typename ...Args>
using is_invoke_res = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;
class BitVec {
    using u8 = std::uint8_t;
    public:
        explicit BitVec(int n) : n(n), nl((n >> LOG_BLOCK_L) + 1), ns((n >> LOG_BLOCK_S) + 1), cum_l(nl), cum_s(ns), bits(ns) {}
        BitVec() : BitVec(0) {}
        template <typename Gen, constraints_t<is_invoke_res<bool, Gen, int>> = nullptr>
        BitVec(int n, Gen gen) : BitVec(n) { build(gen); }
        BitVec& operator=(const BitVec &bv) {
            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = bv.cum_l, cum_s = bv.cum_s, bits = bv.bits;
            return *this;
        }
        BitVec& operator=(BitVec &&bv) {
            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = std::move(bv.cum_l), cum_s = std::move(bv.cum_s), bits = std::move(bv.bits);
            return *this;
        }
        template <typename Gen, constraints_t<is_invoke_res<bool, Gen, int>> = nullptr>
        void build(Gen gen) {
            int i = 0;
            for (int index_s = 1; index_s < ns; ++index_s) {
                int count = cum_s[index_s - 1];
                for (; i < index_s << LOG_BLOCK_S; ++i) {
                    bool b = gen(i);
                    bits[index_s - 1] |= b << (i & MASK_S);
                    count += b;
                }
                if (index_s & ((1 << (LOG_BLOCK_L - LOG_BLOCK_S)) - 1)) cum_s[index_s] = count;                    
                else {
                    int index_l = i >> LOG_BLOCK_L;
                    cum_l[index_l] = cum_l[index_l - 1] + count;
                }
            }
            for (; i < n; ++i) bits[ns - 1] |= gen(i) << (i & MASK_S);
        }
        inline bool operator[](int i) const { return (bits[i >> LOG_BLOCK_S] >> (i & MASK_S)) & 1;}
        inline bool get(int i) const { return (*this)[i];} // returns the i'th val (i: 0-indexed)
        // returns the number of val in [0, i)
        inline int rank(bool val, int i) const {
            int res_1 = cum_l[i >> LOG_BLOCK_L] + cum_s[i >> LOG_BLOCK_S] + popcount8(bits[i >> LOG_BLOCK_S] & ((1 << (i & MASK_S)) - 1));
            return val ? res_1 : i - res_1;
        }
        // returns the number of val in [l, r)
        inline int rank(bool val, int l, int r) const { return rank(val, r) - rank(val, l);}
        // find the index of num'th val. (num: 1-indexed). if not exists, returns default_value.
        int select(bool val, int num, int default_value = -1) const {
            int l = -1, r = n + 1;
            while (r - l > 1) {
                int m = (l + r) >> 1;
                (rank(val, m) >= num ? r : l) = m;
            }
            return r == n + 1 ? default_value : r;
        }
    private:
        static constexpr int LOG_BLOCK_L = 8, LOG_BLOCK_S = 3, MASK_S = (1 << LOG_BLOCK_S) - 1;
        int n, nl, ns;
        std::vector<int> cum_l;
        std::vector<u8> cum_s, bits;

        static constexpr u8 popcount8(u8 x) {
            x = (x & 0b01010101) + ((x >> 1) & 0b01010101);
            x = (x & 0b00110011) + ((x >> 2) & 0b00110011);
            return (x & 0b00001111) + (x >> 4);
        }
};

template <typename T, int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits>
class WaveletMatrix {
    public:
        WaveletMatrix() noexcept : n(0) {}
        template <typename Gen, constraints_t<is_invoke_res<T, Gen, int>> = nullptr>
        WaveletMatrix(int n, Gen generator) : n(n) { build(generator);}
        template <typename U, constraints_t<std::is_constructible<T, U>> = nullptr>
        WaveletMatrix(const std::vector<U> &a) : WaveletMatrix(a.size(), [&a](int i) { return T(a[i]); }) {}
        template <typename Gen, constraints_t<is_invoke_res<T, Gen, int>>  = nullptr>
        void build(Gen generator) {
            std::vector<T> a(n), l(n), r(n);
            for (int i = 0; i < n; ++i) a[i] = generator(i);
            for (int log = bit_num - 1; log >= 0; --log) {
                bv[log] = BitVec(n, [&a, log](int i) -> bool { return (a[i] >> log) & 1; });
                int li = 0, ri = 0;
                for (int i = 0; i < n; ++i) 
                    ((a[i] >> log) & 1 ? r[ri++] : l[li++]) = a[i];
                a.swap(l);
                std::copy(r.begin(), r.begin() + ri, a.begin() + li);
                mid[log] = li;
            }
        }
        T operator[](int i) const {  // returns WaveletMatrix[i]
            T res = 0;
            for (int log = bit_num - 1; log >= 0; --log) {
                bool b = bv[log][i];
                res |= T(b) << log;
                i = b * mid[log] + bv[log].rank(b, i);
            }
            return res;
        }
        inline T get(int i) const { return (*this)[i];}  // returns WaveletMatrix[i]
        int rank(T x, int i) const {  // [0, i)中x的数量
            check_index_bounds(x);
            int l = 0, r = i;
            for (int log = bit_num - 1; log >= 0; --log) succ(l, r, (x >> log) & 1, log);
            return r - l;
        }
        // [l, r) 中第k小 k从0开始
        T range_kth_min(int l, int r, int k, T default_value = T(-1)) const {
            if (k < 0 or k >= r - l) return default_value;
            T res = 0;
            for (int log = bit_num - 1; log >= 0; --log) {
                int cnt_0 = bv[log].rank(false, l, r);
                bool bit = k >= cnt_0;
                succ(l, r, bit, log);
                res |= T(bit) << log;
                k -= bit * cnt_0;
            }
            return res;
        }
        // [l, r) 中第k大 k从0开始
        inline T range_kth_max(int l, int r, int k, T default_value = T(-1)) const {
            return range_kth_min(l, r, r - l - 1 - k, default_value);
        }
        inline T range_min(int l, int r) const { // [l, r)中最小值
            assert(l < r); return range_kth_min(l, r, 0);
        }
        inline T range_max(int l, int r) const { // [l, r)中最大值
            assert(l < r); return range_kth_max(l, r, 0);
        }
        // [l, r) 中小于upper的元素数量
        int range_freq(int l, int r, T upper) const {
            if (r <= l) return 0;
            check_index_bounds(upper);
            int res = 0;
            for (int log = bit_num - 1; log >= 0; --log) {
                bool b = (upper >> log) & 1;
                if (b) res += bv[log].rank(false, l, r);
                succ(l, r, b, log);
            }
            return res;
        }
        // [l, r) 中在区间 [lower, upper) 的元素数量
        inline int range_freq(int l, int r, T lower, T upper) const {
            return range_freq(l, r, upper) - range_freq(l, r, lower);
        }
        // [l, r)中 满足lower <= v 的最小的v
        inline T range_min_geq(int l, int r, T lower, T default_value = T(-1)) const {
            int cnt = range_freq(l, r, lower);
            return cnt >= r - l ? default_value : range_kth_min(l, r, cnt);
        }
        // // [l, r)中 满足lower < v 的最小的v
        inline T range_min_gt(int l, int r, T lower, T default_value = T(-1)) const {
            return lower == MAX ? default_value : range_min_geq(l, r, lower + 1);
        }
        // [l, r)中 满足 v < upper 的最大的v 
        inline T range_max_lt(int l, int r, T upper, T default_value = T(-1)) const {
            int cnt = range_freq(l, r, upper);
            return cnt == 0 ? default_value : range_kth_min(l, r, cnt - 1);
        }
        // [l, r)中 满足 v <= upper 的最大的v 
        inline T range_max_leq(int l, int r, T upper, T default_value = T(-1)) const {
            if (r >= l) return default_value;
            return upper == MAX ? range_max(l, r) : range_max_lt(l, r, upper + 1);
        }
    protected:
        WaveletMatrix(int n) noexcept : n(n) {}
    private:
        static_assert(bit_num > 0);
        static constexpr T MAX = bit_num == std::numeric_limits<T>::digits ? std::numeric_limits<T>::max() : (T(1) << bit_num) - 1;
        const int n;
        std::array<BitVec, bit_num> bv;
        std::array<int, bit_num> mid;

        inline void succ(int &l, int &r, const bool b, const int log) const {
            l = b * mid[log] + bv[log].rank(b, l), r = b * mid[log] + bv[log].rank(b, r);
        }
        static constexpr void check_index_bounds(T val) {
            assert((val >> bit_num) == 0);
        }
};

template <typename T>
class CoordinateCompressorBuilder {
    public:
        struct Compressor {
                static constexpr int absent = -1;
                Compressor() : _xs(std::vector<T>{}) {}
                Compressor(const std::vector<T> &xs) : _xs(xs) { assert(is_strictly_sorted(xs));}
                int size() const { return _xs.size();}
                int comp(const T &e, int default_value = absent) const {
                    const int res = min_geq_index(e);
                    return res != size() and _xs[res] == e ? res : default_value;
                }
                T decomp(const int compres_idx) const { return _xs[compres_idx];}
                int operator[](const T &e) const { return comp(e);}
                int min_geq_index(const T &e) const {
                    return lower_bound(_xs.begin(), _xs.end(), e) - _xs.begin();
                }
            private:
                std::vector<T> _xs;
                static bool is_strictly_sorted(const std::vector<T> &v) {
                    return std::adjacent_find(v.begin(), v.end(), std::greater_equal<T>()) == v.end();
                }
        };
        CoordinateCompressorBuilder() : _xs(std::vector<T>{}) {}
        explicit CoordinateCompressorBuilder(const std::vector<T> &xs) : _xs(xs) {}
        explicit CoordinateCompressorBuilder(std::vector<T> &&xs) : _xs(std::move(xs)) {}
        template <typename Gen, constraints_t<is_invoke_res<T, Gen, int>> = nullptr>
        CoordinateCompressorBuilder(const int n, Gen generator) {
            reserve(n);
            for (int i = 0; i < n; ++i) push(generator(i));
        }
        void reserve(int n) { _xs.reserve(n);}
        void push(const T &first) { _xs.push_back(first);}
        void push(T &&first) {_xs.push_back(std::move(first));}
        template <typename Iterator>
        auto push(const Iterator &first, const Iterator &last) -> decltype(std::vector<T>{}.push_back(*first), void()) {
            for (auto it = first; it != last; ++it) _xs.push_back(*it);
        }
        template <typename Iterable>
        auto push(const Iterable &iterable) -> decltype(std::vector<T>{}.push_back(*iterable.begin()), void()) {
            push(iterable.begin(), iterable.end());
        }
        template <typename ...Args>
        void emplace(Args &&...args) {_xs.emplace_back(std::forward<Args>(args)...);}
        auto build() {
            std::sort(_xs.begin(), _xs.end()), _xs.erase(std::unique(_xs.begin(), _xs.end()), _xs.end());
            return Compressor {_xs};
        }
        static auto build(const std::vector<T> &xs) { return CoordinateCompressorBuilder(xs).build();}
        static auto build(std::vector<T> &&xs) {
            return CoordinateCompressorBuilder(std::move(xs)).build();
        }
        template <typename Gen, constraints_t<is_invoke_res<T, Gen, int>> = nullptr>
        static auto build(const int n, Gen generator) {
            return CoordinateCompressorBuilder<T>(n, generator).build();
        }
    private:
        std::vector<T> _xs;
};

template <typename T, int log_max_len = std::numeric_limits<std::make_unsigned_t<T>>::digits>
class CompressedWaveletMatrix : public WaveletMatrix<int, log_max_len> {
    public:
        CompressedWaveletMatrix() noexcept : WaveletMatrix<int, log_max_len>(0) {}
        template <typename Gen, constraints_t<is_invoke_res<T, Gen, int>> = nullptr>
        CompressedWaveletMatrix(int n, Gen generator) : WaveletMatrix<int, log_max_len>(n), comp(CoordinateCompressorBuilder<T>::build(n, generator)) {
            this->build([this, &generator](int i) { return comp[generator(i)]; });
        }
        template <typename U, constraints_t<std::is_constructible<T, U>> = nullptr>
        CompressedWaveletMatrix(const std::vector<U> &a) : CompressedWaveletMatrix(a.size(), [&a](int i) { return T(a[i]); }) {}
        inline T operator[](int i) const {
            return comp.decomp(WaveletMatrix<int, log_max_len>::operator[](i));
        }
        inline T get(int i) const {
            return (*this)[i];
        }
        inline int rank(T val, int i) const {
            int x = comp.comp(val, -1);
            if (x == -1) return 0; 
            return WaveletMatrix<int, log_max_len>::rank(x, i);
        }
        inline T range_kth_min(int l, int r, int k, T default_value = T(-1)) const {
            int x = WaveletMatrix<int, log_max_len>::range_kth_min(l, r, k, -1);
            return x == -1 ? default_value : comp.decomp(x);
        }
        inline T range_kth_max(int l, int r, int k, T default_value = T(-1)) const {
            int x = WaveletMatrix<int, log_max_len>::range_kth_max(l, r, k, -1);
            return x == -1 ? default_value : comp.decomp(x);
        }
        inline T range_min(int l, int r) const {
            return comp.decomp(WaveletMatrix<int, log_max_len>::range_min(l, r));
        }
        inline T range_max(int l, int r) const {
            return comp.decomp(WaveletMatrix<int, log_max_len>::range_max(l, r));
        }
        inline int range_freq(int l, int r, T upper) const {
            return WaveletMatrix<int, log_max_len>::range_freq(l, r, comp.min_geq_index(upper));
        }
        inline int range_freq(int l, int r, T lower, T upper) const {
            return range_freq(l, r, upper) - range_freq(l, r, lower);
        }
        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower <= v
        inline T range_min_geq(int l, int r, T lower, T default_value = T(-1)) const {
            int x = WaveletMatrix<int, log_max_len>::range_min_geq(l, r, comp.min_geq_index(lower), -1);
            return x == -1 ? default_value : comp.decomp(x);
        }
        // returns the minimum value v in WaveletMatrix[l, r) s.t. lower < v
        inline T range_min_gt(int l, int r, T lower, T default_value = T(-1)) const {
            return lower == std::numeric_limits<T>::max() ? default_value : range_min_geq(l, r, lower + 1, default_value);
        }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. v < upper
        inline T range_max_lt(int l, int r, T upper, T default_value = T(-1)) const {
            int x = WaveletMatrix<int, log_max_len>::range_max_lt(l, r, comp.min_geq_index(upper), -1);
            return x == -1 ? default_value : comp.decomp(x);
        }
        // returns the maximum value v in WaveletMatrix[l, r) s.t. v <= upper
        inline T range_max_leq(int l, int r, T upper, T default_value = T(-1)) const {
            if (r >= l) return default_value;
            return upper == std::numeric_limits<T>::max() ? range_max(l, r) : range_max_lt(l, r, upper + 1, default_value);
        }
    private:
        typename CoordinateCompressorBuilder<T>::Compressor comp;
};


template <class T>
struct Discrete {
    vector<T> xs;
    Discrete(const vector<T>& v) {
        xs = v;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }
    int get(const T& x) const {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    inline int operator()(const T& x) const { return get(x); }
    T operator[](int i) { return xs[i]; }
    int size() const { return xs.size(); }
};

// vector<int> a;
// WaveletMatrix<int, max_log>， wm(a);
// CompressedWaveletMatrix<int, max_log>， wm(a);

void ac_yyf(int tt) {
    rd(n,q);
    vector<int> a(n);
    rd(a);
    Discrete<int> v(a);
    map<int,int>mp;
    f0(n){
        int x=v.get(a[i]);
        mp[x]=a[i];
        a[i]=x;
    }
    WaveletMatrix<int, 18> wm(a);
    f0(q){
        int l,r;
        rd(l,r);
        l--;
        ll c1=mp[a[l]]*1ll*mp[a[r-1]];
        vector<int> mx,mn;
        f2(j,2){
            mn.push_back(mp[wm.range_kth_min(l+1,r-1,j)]);
            mx.push_back(mp[wm.range_kth_max(l+1,r-1,j)]);
        }
        if(c1==0){
            wt(c1,nl);
            continue;
        }
        if(c1<0){
            ll cu=mx[0]*1ll*mn[0];
            ll c=c1*cu;
            cmx(c,c1*mn[0]*mn[1]);
            cmx(c,c1*mx[0]*mx[1]);
             wt(c,nl);
        }else{
            ll cu=mx[0]*1ll*mn[0];
            ll c=c1*cu;
            cmx(c,c1*mn[0]*mn[1]);
            cmx(c,c1*mx[0]*mx[1]);
             wt(c,nl);
        }
        // wt(mx);
        // wt(mn);
        // ll c1=mx[0]*1ll*mx[1]*mx[2]*mx[3];
        // cmx(c1,mn[0]*1ll*mn[1]*mn[2]*mn[3]);
        // cmx(c1,mn[0]*1ll*mn[1]*mx[0]*mx[1]);
        // wt(c1,nl);
    }
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
