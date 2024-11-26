#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using T = int;
T dp(string s) {
	int n = s.size();
	vector f(n, vector<T>(1 << 10, -1));
	function<T(int, int, bool, bool)> dfs = [&](int p, int mask, bool limit, bool is_num) -> T {
		if (p == n) return is_num; 
		if (!limit && is_num && ~f[p][mask]) return f[p][mask];
		T res{};
		if (!is_num) res = dfs(p + 1, mask, false, false);
		int up = limit ? s[p] - '0' : 9;
		for (int i = 1 - is_num; i <= up; ++i) {
			if (!((mask >> i) & 1))
				res += dfs(p + 1, mask | (1 << i), limit && i == up, true);
		}
		if (!limit && is_num)
			f[p][mask] = res;
		return res;
	};
	return dfs(0, 0, true, false);
}

class Solution {
public:
    int numDupDigitsAtMostN(int n) {
    	string s = to_string(n);
    	return n - dp(s);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    Solution so;
    cout << so.numDupDigitsAtMostN(n) << '\n';

    return 0;
}
