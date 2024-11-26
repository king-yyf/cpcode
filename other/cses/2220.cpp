#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-2220

using T = long long;
T dp(string s) {
    int n = s.size();
    vector f(n, vector<T>(10, -1));
    function<T(int, int, bool, bool)> dfs = [&](int p, int pre, bool limit, bool is_num) -> T {
        if (p == n) return is_num; 
        if (!limit && is_num && ~f[p][pre]) return f[p][pre];
        T res{};
        if (!is_num) res = dfs(p + 1, pre, false, false);
        int up = limit ? s[p] - '0' : 9;
        for (int i = 1 - is_num; i <= up; ++i) {
            if (pre != i)
                res += dfs(p + 1, i, limit && i == up, true);
        }
        if (!limit && is_num)
            f[p][pre] = res;
        return res;
    };
    return dfs(0, 0, true, false);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string a, b;
    cin >> a >> b;

    auto chk = [&](string &s) {
        for (int i = 1; i < s.size(); ++i) if (s[i] == s[i - 1]) 
            return 0;
        return 1;
    };

    cout << dp(b) - dp(a) + chk(a) << '\n';

    return 0;
}
