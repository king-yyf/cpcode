#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-2168

template <typename T>
struct FenwickTree {
    int n;
    vector<T> a;
    static int lg(unsigned x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
    FenwickTree(int n) : n(n), a(n) {}
    FenwickTree(vector<T> &A) : FenwickTree((int)A.size()) {
        for (int i = 0; i < n; ++i) add(i, A[i]);
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    T sum(int x) {
        T ans{};
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
    T sum(int l, int r) { //sum[l..r]
        return l <= r ? sum(r) - sum(l - 1) : T{}; 
    }
    T get(int x) const {   // 0 <= x < n, get a[x] in O(1), Equivalent to sum(x, x).
        T s = a[x];
        int y = x + 1;
        y -= y & -y;
        while (x != y) s -= a[x - 1], x -= x & -x;
        return s;
    }
    void set(int x, T v) {  // 0 <= x < n, set a[x] = v
        add(x, v - get(x));
    }
    int kth(T k) const {
        if (k < T()) return -1;
        int x = 0;
        for (int i = 1 << lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i, k -= a[x - 1];
            }
        }
        return x;
    }
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


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<array<int, 3>> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    } 
    sort(a.begin(), a.end(), [&](auto &x, auto &y){
       if (x[0] != y[0]) return x[0] < y[0];
       return x[1] > y[1];
    });

    vector<int> p(n), f(n), g(n);
    for (int i = 0; i < n; ++i) {
        p[i] = a[i][1];
    }

    Discrete<int> v(p);
    int m = v.size();

    FenwickTree<int> fen(m);
    for (int i = n - 1; i >= 0; --i) {
        f[a[i][2]] = fen.sum(0, v(p[i]));
        fen.add(v(p[i]), 1);
    }
    FenwickTree<int> fen2(m);
    for (int i = 0; i < n; ++i) {
        g[a[i][2]] = fen2.sum(v(p[i]), m - 1);
        fen2.add(v(p[i]), 1);
    }

    for (int i = 0; i < n; ++i) {
        cout << f[i] << " \n"[i == n - 1];
    }

    for (int i = 0; i < n; ++i) {
        cout << g[i] << " \n"[i == n - 1];
    }
    
    return 0;
}
