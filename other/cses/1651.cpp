#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
struct RangeAddTree {
    int n;
    vector<T> a;
    RangeAddTree(int N) : n(N), a(N) {}
    RangeAddTree(vector<T> &A) : RangeAddTree((int)A.size()) {
        for (int i = 1; i <= n; i++) {
            a[i - 1] = A[i - 1] - (i > 1 ? A[i - 2] : 0);
            for (int k = (i & -i) >> 1; k > 0; k >>= 1) 
                a[i - 1] += a[i - k - 1];
        }   
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    void add(int l, int r, const T &v) {  // [l, r]
        add(l, v), add(r + 1, -v);
    }
    T get(int x) const {
        T ans = 0;
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m, x;
    cin >> n >> m;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    RangeAddTree<ll> t(a);
    for (int i = 0, op, x, y, u; i < m; ++i) {
    	cin >> op;
        if (op == 1) {
            cin >> x >> y >> u;
            x--, y--;
            t.add(x, y, u);
        } else {
            cin >> u;
            u--;
            cout << t.get(u) << '\n';
        }
    }

    return 0;
}
