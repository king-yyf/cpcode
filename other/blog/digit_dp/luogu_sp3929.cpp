#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// https://www.luogu.com.cn/problem/SP3928

using T = int;
T dp(string &s, int k) {
    int n = s.size();
    vector<vector<T>> f(n, vector<T>(n, -1));
    function<T(int, int, bool, bool)> dfs = [&](int p, int cnt, bool limit, bool is_num) -> T {
        if (p == n) return cnt; 
        if (!limit && is_num && ~f[p][cnt]) return f[p][cnt];
        T res{};
        if (!is_num) res = dfs(p + 1, cnt, false, false);
        int up = limit ? s[p] - '0' : 9;
        for (int i = 1 - is_num; i <= up; ++i) {
            res += dfs(p + 1, cnt + (i == k), limit && i == up, true);
        }
        if (!limit && is_num)
            f[p][cnt] = res;
        return res;
    };
    return dfs(0, 0, true, false);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int a, b;

    while (cin >> a >> b && (a || b)) {
    	if (a > b) swap(a, b);
    	string s = to_string(b), t = to_string(a - 1);

		for (int i = 0; i < 10; ++i) 
			cout << dp(s, i) - dp(t, i) << " \n"[i == 9];
    }
    return 0;
}
