#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using T = int;
T dp(string s) {
	int n = s.size();
	vector f(n, vector<T>(2, -1));
	function<T(int, int, bool)> dfs = [&](int p, int pre, bool limit) -> T {
		if (p == n) return 1; 
		if (!limit && ~f[p][pre]) return f[p][pre];
		T res{};
		int up = limit ? s[p] - '0' : 1;
		for (int i = 0; i <= up; ++i) {
			if (!(pre && i == 1))
				res += dfs(p + 1, i, limit && i == up);
		}
		if (!limit)
			f[p][pre] = res;
		return res;
	};
	return dfs(0, 0, true);
}

class Solution {
public:
    int findIntegers(int n) {
    	string s = bitset<30>(n).to_string(); 
    	return dp(s);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    Solution so;
    cout << so.findIntegers(n) << '\n';

    return 0;
}
