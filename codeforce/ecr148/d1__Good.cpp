#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9 + 1;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k, x, m;
    std::cin >> n >> k >> x >> m;
    
    i64 ans = 1LL * n * (x - m);
    
    std::vector<int> l(n), r(n);
    std::vector<int> cand{0, x - m};
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> r[i];
        ans -= r[i] - l[i];
        if (l[i] <= x - m) {
            cand.push_back(l[i]);
        }
        if (r[i] >= m) {
            cand.push_back(r[i] - m);
        }
    }
    std::sort(cand.begin(), cand.end());
    
    cand.erase(std::unique(cand.begin(), cand.end()), cand.end());
    
    cand.insert(cand.begin(), -inf);
    cand.push_back(inf);
    
    int N = cand.size();
    
    std::vector<int> o(n);
    std::iota(o.begin(), o.end(), 0);
    std::sort(o.begin(), o.end(), [&](int i, int j) {
        return l[i] + r[i] < l[j] + r[j];
    });
    
    std::vector f(N, std::vector<i64>(N));
    for (int i = 1, L = 0; i < N; i++) {
        while (L < n && l[o[L]] + r[o[L]] - m < 2 * cand[i]) {
            L++;
        }
        int R = L;
        i64 sum = 0;
        for (int j = i + 1; j < N; j++) {
            while (R < n && (j == N - 1 || l[o[R]] + r[o[R]] - m < cand[i] + cand[j])) {
                sum += std::max(0, std::min(cand[i] + m, r[o[R]]) - std::max(cand[i], l[o[R]]));
                R++;
            }
            f[i][j] += sum;
        }
    }
    for (int j = N - 2, R = n; j >= 0; j--) {
        while (R && l[o[R - 1]] + r[o[R - 1]] - m >= 2 * cand[j]) {
            R--;
        }
        int L = R;
        i64 sum = 0;
        for (int i = j - 1; i >= 0; i--) {
            while (L && (i == 0 || l[o[L - 1]] + r[o[L - 1]] - m >= cand[i] + cand[j])) {
                L--;
                sum += std::max(0, std::min(cand[j] + m, r[o[L]]) - std::max(cand[j], l[o[L]]));
            }
            f[i][j] += sum;
        }
    }
    
    k++;
    
    i64 lo = 0, hi = 1E13;
    
    auto get = [&](i64 x) {
        std::vector<i64> dp(N, -1E18);
        dp[0] = 0;
        std::vector<int> cnt(N);
        
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (dp[j] < dp[i] + f[i][j] - x) {
                    dp[j] = dp[i] + f[i][j] - x;
                    cnt[j] = cnt[i] + 1;
                }
            }
        }
        
        return std::pair(dp[N - 1], cnt[N - 1]);
    };
    
    while (lo + 1 < hi) {
        i64 m = (lo + hi) / 2;
        auto [val, cnt] = get(m);
        if (cnt < k) {
            hi = m;
        } else {
            lo = m;
        }
    }
    
    auto [vl, cl] = get(lo);
    auto [vr, cr] = get(hi);
    
    ans += std::min(vl + lo * k, vr + hi * k);
    
    std::cout << ans << "\n";
    
    return 0;
}