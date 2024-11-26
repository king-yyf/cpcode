#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> a;
    FenwickTree(int n) : n(n), a(n) {}
    FenwickTree(vector<T> &A) : FenwickTree((int)A.size()) {
        for (int i = 0; i < n; ++i) add(i, A[i]);
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    T ask(int x) {
        T ans = 0;
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
    T ask(int l, int r) { //sum[l..r]
        if (l > r) return 0;
        return ask(r) - ask(l - 1);
    }
};


int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    
    int n, k, x;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
    	cin >> x;
    	a[i] -= x;
    }
    auto v = a;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    FenwickTree<int> t(n);

    auto get = [&](long long x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin();
    };

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
    	ans += t.ask(get(v[i] + k));
    	t.add(get(v[i]), 1);
    }
    cout << ans << "\n";
    return 0;
}
