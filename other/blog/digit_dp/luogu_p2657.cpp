#include <bits/stdc++.h>
using namespace std;

// https://www.luogu.com.cn/problem/P2657

using T = int;
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
			if (abs(i - pre) >= 2)
				res += dfs(p + 1, i, limit && i == up, true);
		}
		if (!limit && is_num)
			f[p][pre] = res;
		return res;
	};
	return dfs(0, -2, true, false);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

	string s = to_string(b), t = to_string(a - 1);
	cout << dp(s) - dp(t) << '\n';

    return 0;
}