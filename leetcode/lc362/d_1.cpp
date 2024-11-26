#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

template <typename T>
vector<int> kmp_table(const T &s) {
    int n = s.size(), k = 0;
    vector<int> p(n);
    for (int i = 1; i < n; ++i) {
        while (k > 0 && !(s[i] == s[k])) k = p[k - 1];
        if (s[i] == s[k]) k++;
        p[i] = k;
    }
    return p;
}
template <typename T>
vector<int> kmp(const T &s, const T &t) {  // return s在t中所有出现下标
    vector<int> res, p = kmp_table(s);
    int n = s.size(), m = t.size(), k = 0;
    for (int i = 0; i < m; ++i) {
        while (k && (k == n || !(t[i] == s[k]))) k = p[k - 1];
        if (t[i] == s[k]) k++;
        if (k == n) res.push_back(i - n + 1);
    }
    return res;
}

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
using mint = static_mod<1000000007>; // 1000000007

class Solution {
public:
    int numberOfWays(string s, string t, long long k) {
    	int n = s.size();
    	auto p = kmp(t, s + s.substr(0, n -1));
        int x = p.size(), y = n - x, p1 = x && p[0] == 0, p2 = p1 ^ 1;
        Mat<mint> A({{x - 1, x}, {y, y - 1}});
        auto T = A.pow(k);
        return (T[0][0] * p1 + T[0][1] * p2).val();
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    

    return 0;
}
