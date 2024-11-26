#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
#include <cstdio>

using namespace std;

// https://www.spoj.com/problems/BALNUM/


using T = unsigned long long;
const int N = 20;
T f[N][1 << 10][1 << 10];
T dp(string &s) {
    int n = s.size();
    function<T(int, int, int, bool, bool)> dfs = [&](int p, int st, int mask, bool limit, bool is_num) -> T {
        if (p == n) {
            bool o = 1;
            for (int i = 0; i < 10; ++i) {
                if ((st >> i & 1) && (mask >> i & 1) == (i & 1)) o = 0;
            }
            return is_num && o;
        }
        if (!limit && is_num && ~f[p][st][mask]) return f[p][st][mask];
        T res{};
        if (!is_num) res = dfs(p + 1, st, mask, false, false);
        int up = limit ? s[p] - '0' : 9;
        for (int i = 1 - is_num; i <= up; ++i) {
            res += dfs(p + 1, st | (1 << i), mask ^ (1 << i), limit && i == up, true);
        }
        if (!limit && is_num)
            f[p][st][mask] = res;
        return res;
    };
    return dfs(0, 0, 0, true, false);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    T a, b;
    int t;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        string s = to_string(b), t = to_string(a - 1);
        memset(f, -1, sizeof(f));
        auto x = dp(s);
        memset(f, -1, sizeof(f));
        auto y = dp(t);
        cout << x - y << '\n';
    }
    return 0;
}
