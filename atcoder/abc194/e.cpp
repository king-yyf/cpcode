#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://atcoder.jp/contests/abc194/tasks/abc194_e

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
    template<typename Fn>
    int partition(Fn f) {
        int j = -1;
        T t{};
        for (int i = 1 << lg(n); i; i >>= 1) {
            if (j + i < n && !f(j + i, t + a[j + i])) 
                t += a[j += i];
        }
        return j + 1;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    int ans = n;

    vector<int> a(n), cnt(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];    
    }

    FenwickTree<int> f(n);

    for (int i = 0; i < n; ++i) {
        if (++cnt[a[i]] == 1) f.set(a[i], 1);
        if (i >= m && --cnt[a[i - m]] == 0) {
            f.set(a[i - m], 0);
        }
        if (i >= m - 1) {
            ans = min(ans, f.partition([&](int i, int t){return t < i + 1;}));
        }
    }

    cout << ans << '\n';

    return 0;
}
