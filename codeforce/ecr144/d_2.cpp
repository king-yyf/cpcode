#include<bits/stdc++.h>
using namespace std;

template <class S, S (*op)(S, S), S (*e)()>
struct SegTree {
    int n, size, log;
    vector<S> d;
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<S>(n, e())) {}
    explicit SegTree(const vector<S> &v) : n(int(v.size())) {
        log = ceil_pow2(n), size = 1 << log;
        d = vector<S>(2 * size, e());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) pull(i);
    }

    int ceil_pow2(int n) {  // minimum non-neg x s.t. `n <= 2^x`
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }
    void set(int p, S x) {  // assert(0 <= p < n)
        p += size, d[p] = x;
        for (int i = 1; i <= log; ++i) pull(p >> i);
    }
    S get(int p) const { return d[p + size];}
    S get(int l, int r) {   // [l, r)
        S sl = e(), sr = e();
        l += size, r += size;
        while (l < r) {
            if (l & 1) sl = op(sl, d[l++]);
            if (r & 1) sr = op(d[--r], sr);
            l >>= 1, r >>= 1;
        }
        return op(sl, sr);
    }
    S get_all() const {return d[1];}

    void pull(int k) {
        d[k] = op(d[2 * k], d[2 * k + 1]);
    }
    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F>     // 0 <= l <= n, f(e()) is true
    int max_right(int l, F f) const { 
        if (l == n) return n;
        l += size;
        S x = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(x, d[l]))) {
                while (l < size) {
                    l = 2 * l;
                    if (f(op(x, d[l]))) {
                        x = op(x, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            x = op(x, d[l]);
            l++;
        } while ( (l & -l) != l);
        return n;
    }
    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F>  // 0 <= r <= n, f(e()) is true
    int min_left(int r, F f) const {
        if (r == 0) return 0;
        r += size;
        S x = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], x))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], x))) {
                        x = op(d[r], x);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            x = op(d[r], x);
        } while ((r & -r) != r);
        return 0;
    }
};

struct S {
    long long max_sum;
    long long all_sum;
    long long left_suf;
    long long right_pref;
    S(): max_sum(0), all_sum(0), left_suf(0), right_pref(0) {}
    S(long long ms, long long as, long long ls, long long rp) :
    max_sum(ms),all_sum(as),left_suf(ls),right_pref(rp) {}
};

S op(S x, S y) {
    S res;
    res.all_sum = x.all_sum + y.all_sum;
    res.left_suf = max(x.left_suf, x.all_sum + y.left_suf);
    res.right_pref = max(y.right_pref, y.all_sum + x.right_pref);
    res.max_sum = max({x.max_sum, y.max_sum, x.right_pref + y.left_suf});
    return res;
}

S e() {
    return S();
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
	cout << fixed << setprecision(10);

    int n, q;
    cin >> n >> q;
    vector<S> a(n);
    long long x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        a[i] = S{x, x, x, x}; 
    }
    SegTree<S,op,e> seg(a);
    long long mx = max(0ll, seg.get_all().max_sum);
    cout << mx << "\n";
    for (int i = 0, op, x, y; i < q; ++i) {
        cin >> x >> y;
        seg.set(x, S{y, y,y,y});
        long long mx = max(0ll, seg.get_all().max_sum);
        cout << mx << "\n";
    }
}