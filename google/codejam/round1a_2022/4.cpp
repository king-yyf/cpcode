#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    i64 sum = 0;
    for (int i = 0; i < 30; i++) {
        sum += 1 << i;
        std::cout << (1 << i) << " ";
    }
    
    std::vector<int> a;
    for (int i = 0; i < n - 30; i++) {
        a.push_back(1000000000 - i);
        sum += 1000000000 - i;
        std::cout << 1000000000 - i << " ";
    }
    std::cout << std::endl;
    
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        a.push_back(x);
        sum += x;
    }
    sum /= 2;
    std::vector<int> s;
    for (auto x : a) {
        if (sum >= x) {
            s.push_back(x);
            sum -= x;
        }
    }
    for (int i = 29; i >= 0; i--) {
        if (sum >> i & 1) {
            sum -= 1 << i;
            s.push_back(1 << i);
        }
    }
    for (auto x : s) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    for (int i = 1; i <= t; i++) {
        solve();
    }
    
    return 0;
}