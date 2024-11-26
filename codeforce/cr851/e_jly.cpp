#include <bits/stdc++.h>

using i64 = long long;
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n = 0) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

struct Max {
    int v;
    Max(int x = -1E9) : v{x} {}
    
    Max &operator+=(Max a) {
        v = std::max(v, a.v);
        return *this;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<i64> s(n + 1);
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }
    
    auto v = s;
    std::sort(v.begin(), v.end());
    
    Fenwick<Max> fen(n + 1);
    
    std::vector<int> dp(n + 1);
    for (int i = 0; i <= n; i++) {
        int x = std::lower_bound(v.begin(), v.end(), s[i]) - v.begin();
        if (i == 0) {
            dp[i] = 0;
        } else {
            dp[i] = std::max(dp[i - 1], i + fen.sum(x + 1).v);
        }
        fen.add(x, dp[i] - i);
    }
    
    std::cout << dp[n] << "\n";
    
    return 0;
}