#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int b;
        std::cin >> b;
        a[i] -= b;
    }
    
    int x = *std::max_element(a.begin(), a.end());
    
    std::vector<int> p;
    for (int i = 0; i < n; i++) {
        if (a[i] == x) {
            p.push_back(i);
        }
    }
    std::cout << p.size() << "\n";
    for (int i = 0; i < p.size(); i++) {
        std::cout << p[i] + 1 << " \n"[i == p.size() - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}