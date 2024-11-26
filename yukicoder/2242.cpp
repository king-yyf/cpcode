#include <bits/stdc++.h>
using namespace std;

// https://yukicoder.me/problems/no/2242

/*


準備として、{0,1,⋯,N} から {0,1,⋯,N} への写像（関数）G を次のように定めます。

G(k) の意味として、番号 k 以下の任意の町に行くことができるなら、そこから 1 回以内の移動で G(k) 以下の任意の町に行くことができます。なぜなら、番号 
k 以下の町 j から行くことができる町は標高が Tj 以下の任意の町であるので、j=1,2,⋯,k について考えると 
1 回以内の移動で標高が 
max{T1,T2,⋯,Tk} 以下の町に行くことができ、さらに H は単調増加であるからです。また、番号 k 以下の町はすでに行くことができているので、番号 k 以下の任意の町に行けるなら、そこから 1 回以内のの移動で番号 
G(k) 以下の任意の町に行くことができます。


*/

void wt(vector<int> &a) {
    for (int x : a)
        cout << x << ' ';
    cout << '\n';
}

using ll = long long;

// 预处理 O(NlogN)；查询：O(logN)
struct BiLifting {
    int N, INVALID, lgD;
    vector<vector<int>> mat;
    BiLifting() : N(0), lgD(0) {}
    BiLifting(const vector<int> &vec_nxt, int INVALID = -1, int lgd = 0)
        : N(vec_nxt.size()), INVALID(INVALID), lgD(lgd) {
        while ((1LL << lgD) < N) lgD++;
        mat.assign(lgD, vector<int>(N, INVALID));
        mat[0] = vec_nxt;
        for (int i = 0; i < N; i++)
            if (mat[0][i] < 0 or mat[0][i] >= N) mat[0][i] = INVALID;
        for (int d = 0; d < lgD - 1; d++) {
            for (int i = 0; i < N; i++)
                if (mat[d][i] != INVALID) mat[d + 1][i] = mat[d][mat[d][i]];
        }
    }
    int kth_next(int now, long long k) {
        if (k >= (1LL << lgD)) exit(8);
        for (int d = 0; k and now != INVALID; d++, k >>= 1)
            if (k & 1) now = mat[d][now];
        return now;
    }

    // Distance from l to [r, infty)
    // Requirement: mat[0][i] > i for all i (monotone increasing)
    int distance(int l, int r) {
        if (l >= r) return 0;
        int ret = 0;
        for (int d = lgD - 1; d >= 0; d--) {
            if (mat[d][l] < r and mat[d][l] != INVALID) ret += 1 << d, l = mat[d][l];
        }
        if (mat[0][l] == INVALID or mat[0][l] >= r)
            return ret + 1;
        else
            return -1; // Unable to reach
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
    vector<int> h(n), t(n);
    for (int &x : h)
        cin >> x;
    for (int &x : t)
        cin >> x;

    auto z = h;
    z.insert(z.end(), t.begin(), t.end());
    Discrete<int> v(z);

    for (auto &x : h) 
        x = v(x);
    for (auto &x : t) 
        x = v(x);
    int m = v.size();
    vector<int> g(m);
    wt(h);
    wt(t);
    iota(g.begin(), g.end(), 0);
    for (int i = 0; i < n; ++i) 
        g[h[i]] = max(g[h[i]], t[i]);
    wt(g);
    for (int i = 1; i < m; ++i)
        g[i] = max(g[i], g[i - 1]);

    BiLifting bl(g);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        int l = t[x], r = h[y];
        auto c = bl.distance(l, r);
        if (c >= 0) c++;
        cout << c << '\n';
    }
   
    return 0;
}
