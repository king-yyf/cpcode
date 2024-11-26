#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using T = int;
T dp(string s) {
	int n = s.size();
	vector f(n, vector<T>(2, -1));
	int st[10] = {0, 0, 1, -1, -1, 1, 1, -1, 0, 1};
	function<T(int,bool, bool)> dfs = [&](int p, bool has_diff, bool limit) -> T {
		if (p == n) return has_diff; 
		if (!limit && ~f[p][has_diff]) return f[p][has_diff];
		T res{};
		int up = limit ? s[p] - '0' : 9;
		for (int i = 0; i <= up; ++i) {
			if (~st[i]) {
				res += dfs(p + 1, has_diff | st[i], limit && i == up);
			}
		}
		if (!limit)
			f[p][has_diff] = res;
		return res;
	};
	return dfs(0, false, true);
}

class Solution {
public:
    int rotatedDigits(int n) {
    	string s = to_string(n);
    	return dp(s);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    Solution so;
    cout << so.rotatedDigits(n) << '\n';

    return 0;
}
