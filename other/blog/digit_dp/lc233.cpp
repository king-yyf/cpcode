#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using T = int;
T dp(string s) {
	int n = s.size();
	vector f(n, vector<T>(n, -1));
	function<T(int, int, bool, bool)> dfs = [&](int p, int cnt, bool limit, bool is_num) -> T {
		if (p == n) return cnt; 
		if (!limit && is_num && ~f[p][cnt]) return f[p][cnt];
		T res{};
		if (!is_num) res = dfs(p + 1, cnt, false, false);
		int up = limit ? s[p] - '0' : 9;
		for (int i = 1 - is_num; i <= up; ++i) {
			res += dfs(p + 1, cnt + (i == 1), limit && i == up, true);
		}
		if (!limit && is_num)
			f[p][cnt] = res;
		return res;
	};
	return dfs(0, 0, true, false);
}

class Solution {
public:
    int countDigitOne(int n) {
    	string s = to_string(n);
    	return dp(s);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    Solution so;
    cout << so.countDigitOne(n) << '\n';

    return 0;
}
