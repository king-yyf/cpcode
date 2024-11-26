#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <class S, S (*op)(S, S), S (*e)()>
struct SegTree {
    int n, size, log;
    vector<S> d;
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<S>(n, e())) {}
    explicit SegTree(const vector<S> &v) : n(int(v.size())) {
        log = ceil_lg(n), size = 1 << log;
        d = vector<S>(2 * size, e());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) pull(i);
    }
    int ceil_lg(int x) {   // minimum non-neg x s.t. `n <= 2^x`
        return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);
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

    void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]);}
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
                    l = (2 * l);
                    if (f(op(x, d[l]))) {
                        x = op(x, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            x = op(x, d[l]);
            l++;
        } while ((l & -l) != l);
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



class Eratosthenes{
    public:
    int m;
    vector<bool> is_prime;
    vector<int> primes;
    Eratosthenes(int m_){
        m = m_;
        init();
    }
    private:
    void init(){
        is_prime.assign(m+1, true);
        is_prime[0] = false, is_prime[1] = false;
        for(int i = 2; i <= m; i++){
            if(is_prime[i]){
                primes.push_back(i);
                for(int j = 2; i*j <= m; j++) is_prime[i*j] = false;
            }
        }
    }
};

const int N = 5000000;
auto et = Eratosthenes(N);

int tot[N+1];
int depth[N+1];

void init(){
    for(int x = 1; x <= N; x++) tot[x] = x;
    for(int p: et.primes){
        for(int i = 1; i*p <= N; i++){
            tot[i*p] /= p;
            tot[i*p] *= p-1;
        }
    }
    int mx = 0;
    for(int x = 2; x <= N; x++) {
        depth[x] = depth[tot[x]]+1;
        mx = max(mx, depth[x]);
    }
}

const int inf = 1e9;

int calc_max(int x, int y){
    return max(x, y);
}

int neg_inf(){
    return -inf;
}

int calc_min(int x, int y){
    return min(x, y);
}

int pos_inf(){
    return inf;
}


int add(int x, int y){
    return x+y;
}

int zero(){
    return 0;
}

int lca(int x, int y){
    if(x == zero()) return y;
    if(y == zero()) return x;
    if(depth[x] > depth[y]){
        swap(x, y);
    }
    while(depth[y] > depth[x]){
        y = tot[y];
    }
    while(x != y){
        x = tot[x];
        y = tot[y];
    }
    return x;
}

using SegMax = SegTree<int, calc_max, neg_inf>;
using SegLca = SegTree<int, lca, zero>;
using SegSum = SegTree<int, add, zero>;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    init();
    int n, m; cin >> n >> m;
    vector<int> a(n);
    vector<int> d(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        d[i] = depth[a[i]];
    }
    SegMax seg_max(a);
    SegSum seg_sum(d);
    SegLca seg_lca(a);
    // print_vector(d);
    while(m--){
        int t, l, r; cin >> t >> l >> r; l--;
        if(t == 1){
            auto g = [&](int x){
                return x <= 1;
            };
            int cur_l = l;
            while(true){
                auto rr = seg_max.max_right(cur_l, g);
                if(rr >= r) break;
                a[rr] = tot[a[rr]];
                seg_max.set(rr, a[rr]);
                seg_sum.set(rr, depth[a[rr]]);
                seg_lca.set(rr, a[rr]);
                cur_l = rr+1;
                if(cur_l >= r) break;
            }
        }else{
            int lc = seg_lca.get(l, r);
            cout << seg_sum.get(l, r)-depth[lc]*(r-l) << '\n';
        }
    }

    return 0;
}

