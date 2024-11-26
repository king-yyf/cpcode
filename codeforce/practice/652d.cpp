#include <bits/stdc++.h>
using namespace std;

using ll = long long;


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
        T ans = 0;
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
    T sum(int l, int r) { //sum[l..r]
        return l <= r ? sum(r) - sum(l - 1) : 0; 
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
    int n;
    cin >> n;
    vector<array<int,3> > a(n);
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }

    
    sort(a.begin(), a.end(), [&](auto &x, auto &y){
    	return x[1] < y[1];
    });

    for (int i = 0; i < n; ++i) 
    	p[i] = a[i][0];

    Discrete<int> v(p);
    int m = v.size();
    FenwickTree<int> f(m + 1);


    vector<int> ans(n);

    for (int i = 0; i < n; ++i) {
    	ans[a[i][2]] = f.sum(v(a[i][0]), m);
    	f.add(v(a[i][0]), 1);
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << "\n";	
    }

    return 0;
}
