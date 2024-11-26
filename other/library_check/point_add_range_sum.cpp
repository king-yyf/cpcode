#include <bits/stdc++.h>
using namespace std;

// https://judge.yosupo.jp/problem/point_add_range_sum

using ll = long long;

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


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    FenwickTree<long long> f(a);

    for (int i = 0; i < q; ++i) {
    	int t, l, r;
    	cin >> t >> l >> r;
        if (t == 0) {
            f.add(l, r);
        } else 
    	    cout << f.sum(l, r - 1) << '\n';
    }

    return 0;
}
