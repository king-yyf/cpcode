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
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
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

template <typename T>
struct Mat {
    vector<vector<T>> dat;

    Mat() = default;
    Mat(int n) : Mat(n, n) {}
    Mat(int n, int m, T fill_value = T(0)) : dat(n, vector<T>(m, fill_value)) {}
    Mat(const vector<vector<T>>& dat) : dat(dat) {}

    const vector<T>& operator[](int i) const { return dat[i]; }
    vector<T>& operator[](int i) { return dat[i]; }

    operator vector<vector<T>>() const { return dat; }

    friend bool operator==(const Mat<T>& A, const Mat<T>& B) { return A.dat == B.dat; }
    friend bool operator!=(const Mat<T>& A, const Mat<T>& B) { return A.dat != B.dat; }

    pair<int, int> shape() const { return dat.empty() ? make_pair<int, int>(0, 0) : make_pair<int, int>(dat.size(), dat[0].size()); }
    int row_size() const { return dat.size(); }
    int col_size() const { return dat.empty() ? 0 : dat[0].size(); }

    friend Mat<T>& operator+=(Mat<T>& A, const Mat<T>& B) {
        assert(A.shape() == B.shape());
        auto [n, m] = A.shape();
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) A.dat[i][j] += B.dat[i][j];
        return A;
    }
    friend Mat<T>& operator-=(Mat<T>& A, const Mat<T>& B) {
        assert(A.shape() == B.shape());
        auto [n, m] = A.shape();
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) A.dat[i][j] -= B.dat[i][j];
        return A;
    }
    friend Mat<T>& operator*=(Mat<T>& A, const Mat<T>& B) { return A = A * B; }
    friend Mat<T>& operator*=(Mat<T>& A, const T& val) {
        for (auto& row : A.dat) for (auto& elm : row) elm *= val;
        return A;
    }
    friend Mat<T>& operator/=(Mat<T>& A, const T& val) { return A *= T(1) / val; }
    friend Mat<T>& operator/=(Mat<T>& A, const Mat<T>& B) { return A *= B.inv(); }

    friend Mat<T> operator+(Mat<T> A, const Mat<T>& B) { A += B; return A; }
    friend Mat<T> operator-(Mat<T> A, const Mat<T>& B) { A -= B; return A; }
    friend Mat<T> operator*(const Mat<T>& A, const Mat<T>& B) {
        assert(A.col_size() == B.row_size());
        const int n = A.row_size(), m = A.col_size(), l = B.col_size();

        if (min({ n, m, l }) <= 70) {
            Mat<T> C(n, l);
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < l; ++k) {
                C.dat[i][k] += A.dat[i][j] * B.dat[j][k];
            }
            return C;
        }
        // strassen
        const int nl = 0, nm = n >> 1, nr = nm + nm;
        const int ml = 0, mm = m >> 1, mr = mm + mm;
        const int ll = 0, lm = l >> 1, lr = lm + lm;
        auto A00 = A.submat(nl, nm, ml, mm), A01 = A.submat(nl, nm, mm, mr);
        auto A10 = A.submat(nm, nr, ml, mm), A11 = A.submat(nm, nr, mm, mr);
        auto B00 = B.submat(ml, mm, ll, lm), B01 = B.submat(ml, mm, lm, lr);
        auto B10 = B.submat(mm, mr, ll, lm), B11 = B.submat(mm, mr, lm, lr);
        auto P0 = (A00 + A11) * (B00 + B11), P1 = (A10 + A11) * B00;
        auto P2 = A00 * (B01 - B11), P3 = A11 * (B10 - B00);
        auto P4 = (A00 + A01) * B11, P5 = (A10 - A00) * (B00 + B01), P6 = (A01 - A11) * (B10 + B11);

        Mat<T> C(n, l);

        C.assign_submat(nl, ll, P0 + P3 - P4 + P6), C.assign_submat(nl, lm, P2 + P4);
        C.assign_submat(nm, ll, P1 + P3), C.assign_submat(nm, lm, P0 + P2 - P1 + P5);
        if (l != lr) for (int i = 0; i < nr; ++i) for (int j = 0; j < mr; ++j) C.dat[i][lr] += A.dat[i][j] * B.dat[j][lr];
        if (m != mr) for (int i = 0; i < nr; ++i) for (int k = 0; k < l; ++k) C.dat[i][k] += A.dat[i][mr] * B.dat[mr][k];
        if (n != nr) for (int j = 0; j < m; ++j) for (int k = 0; k < l; ++k) C.dat[nr][k] += A.dat[nr][j] * B.dat[j][k];

        return C;
    }
    friend Mat<T> operator*(const T& val, Mat<T> A) { A *= val; return A; }
    friend Mat<T> operator*(Mat<T> A, const T& val) { A *= val; return A; }
    friend Mat<T> operator/(const Mat<T>& A, const Mat<T>& B) { return A * B.inv(); }
    friend Mat<T> operator/(Mat<T> A, const T& val) { A /= val; return A; }
    friend Mat<T> operator/(const T& val, const Mat<T>& A) { return val * A.inv(); }

    friend vector<T> operator*(const Mat<T>& A, const vector<T>& x) {
        const auto [n, m] = A.shape();
        assert(m == int(x.size()));
        vector<T> b(n, T(0));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) b[i] += A.dat[i][j] * x[j];
        return b;
    }

    static Mat<T> e0(int n) { return Mat<T>(n, Identity::ADD); }
    static Mat<T> e1(int n) { return Mat<T>(n, Identity::MUL); }

    Mat<T> pow(long long b) const {
        assert_square();
        assert(b >= 0);
        Mat<T> res = e1(row_size()), p = *this;
        for (; b; b >>= 1) {
            if (b & 1) res *= p;
            p *= p;
        }
        return res;
    }
    Mat<T> inv() const { return *safe_inv(); }

    optional<Mat<T>> safe_inv() const {
        assert_square();
        Mat<T> A = *this;
        const int n = A.row_size();
        for (int i = 0; i < n; ++i) {
            A[i].resize(2 * n, T{ 0 });
            A[i][n + i] = T{ 1 };
        }
        for (int i = 0; i < n; ++i) {
            for (int k = i; k < n; ++k) if (A[k][i] != T{ 0 }) {
                swap(A[i], A[k]);
                T c = T{ 1 } / A[i][i];
                for (int j = i; j < 2 * n; ++j) A[i][j] *= c;
                break;
            }
            if (A[i][i] == T{ 0 }) return nullopt;
            for (int k = 0; k < n; ++k) if (k != i and A[k][i] != T{ 0 }) {
                T c = A[k][i];
                for (int j = i; j < 2 * n; ++j) A[k][j] -= c * A[i][j];
            }
        }
        for (auto& row : A.dat) row.erase(row.begin(), row.begin() + n);
        return A;
    }

    T det() const {
        assert_square();
        Mat<T> A = *this;
        bool sgn = false;
        const int n = A.row_size();
        for (int j = 0; j < n; ++j) for (int i = j + 1; i < n; ++i) if (A[i][j] != T{ 0 }) {
            swap(A[j], A[i]);
            T q = A[i][j] / A[j][j];
            for (int k = j; k < n; ++k) A[i][k] -= A[j][k] * q;
            sgn = not sgn;
        }
        T res = sgn ? T{ -1 } : T{ +1 };
        for (int i = 0; i < n; ++i) res *= A[i][i];
        return res;
    }
    T det_arbitrary_mod() const {
        assert_square();
        Mat<T> A = *this;
        bool sgn = false;
        const int n = A.row_size();
        for (int j = 0; j < n; ++j) for (int i = j + 1; i < n; ++i) {
            for (; A[i][j].val(); sgn = not sgn) {
                swap(A[j], A[i]);
                T q = A[i][j].val() / A[j][j].val();
                for (int k = j; k < n; ++k) A[i][k] -= A[j][k] * q;
            }
        }
        T res = sgn ? -1 : +1;
        for (int i = 0; i < n; ++i) res *= A[i][i];
        return res;
    }
    void assert_square() const { assert(row_size() == col_size()); }

    Mat<T> submat(int r1, int r2, int c1, int c2) const {
        Mat<T> A(r2 - r1, c2 - c1);
        for (int i = r1; i < r2; ++i) for (int j = c1; j < c2; ++j) {
            A[i - r1][j - c1] = dat[i][j];
        }
        return A;
    }
    void assign_submat(int r1, int c1, const Mat<T>& A) {
        const int n = A.row_size(), m = A.col_size();
        assert(r1 + n <= row_size() and c1 + m <= col_size());
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
            dat[r1 + i][c1 + j] = A[i][j];
        }
    }
private:
    enum class Identity { ADD, MUL };
    Mat(int n, Identity ident) : Mat<T>::Mat(n) {
        if (ident == Identity::MUL) for (int i = 0; i < n; ++i) dat[i][i] = 1;
    }
};

using ull = unsigned long long;
ll inverse(ll a, ll m) { 
    a %= m; if (a == 0) return 0; if (a < 0) a += m;
    ll u = 0, v = 1;
    while (a) { ll t = m / a;  m -= t * a; swap(a, m); u -= t * v; swap(u, v); }
    return u;
}
struct barrett {
    unsigned int _m;
    ull im;
    explicit barrett(unsigned int m) : _m(m), im((ull)(-1) / m + 1) {} // 1 <= m < 2^31
    unsigned int umod() const { return _m; }
    unsigned int mul(unsigned int a, unsigned int b) const { // 0 <= a, b < m, return a * b % m
        ull z = a; z *= b;
        ull x = (ull)(((unsigned __int128)(z)*im) >> 64);
        unsigned int v = (unsigned int)(z - x * _m);
        if (_m <= v) v += _m;
        return v;
    }
};
template <int id> struct dynamic_mod {
    using mint = dynamic_mod;
    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) { assert(1 <= m); bt = barrett(m);}
    static mint raw(int v) { mint x; x._v = v; return x;}
    dynamic_mod() : _v(0) {}
    template <class T>
    dynamic_mod(T v) { ll x = (ll)(v % (ll)(mod())); if (x < 0) x += mod(); _v = (unsigned int)(x);}
    dynamic_mod(unsigned int v) { _v = (unsigned int)(v % mod());}
    unsigned int val() const { return _v; }
    mint& operator++() { _v++; if (_v == umod()) _v = 0; return *this;}
    mint& operator--() { if (_v == 0) _v = umod(); _v--; return *this;}
    mint operator++(int) { mint result = *this; ++*this; return result;}
    mint operator--(int) { mint result = *this; --*this; return result;}
    mint& operator+=(const mint& rhs) { _v += rhs._v; if (_v >= umod()) _v -= umod(); return *this;}
    mint& operator-=(const mint& rhs) { _v += mod() - rhs._v; if (_v >= umod()) _v -= umod(); return *this;}
    mint& operator*=(const mint& rhs) { _v = bt.mul(_v, rhs._v); return *this;}
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(ll n) const { assert(0 <= n); mint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1;}return r;}
    mint inv() const { return inverse(_v, mod()); }
    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs;}
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs;}
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs;}
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v;}
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v;}
private:
    unsigned int _v;
    static barrett bt;
    static unsigned int umod() { return bt.umod(); }
};
template <int id> barrett dynamic_mod<id>::bt(998244353);
using modint = dynamic_mod<998244353>;


void ac_yyf(int tt) {
    int x0, x1, a, b, m;
    cin >> x0 >> x1 >> a >> b;
    string n;
    cin >> n >> m;
    modint::set_mod(m);
    Mat<modint> A({{0, 1}, {b, a}});
    Mat<modint> ans = Mat::e1();
    for (int i = 0; i < n.size(); ++i) {
    	ans = ans.pow(10) * A.pow(s[i] - '0');
    }
    cout << (ans[0][0] * x0 + ans[0][1] * x1).val() << '\n';
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
