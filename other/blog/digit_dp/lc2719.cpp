#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int M = 1000000007;
using T = int;
T dp(string &s, int mn_sum, int mx_sum) {
	int n = s.size();
	vector f(n, vector<T>(mx_sum + 1, -1));
	function<T(int, int, bool)> dfs = [&](int p, int sum, bool limit) -> T {
		if (sum > mx_sum) return 0;
		if (p == n) return sum >= mn_sum; 
		if (!limit && ~f[p][sum]) return f[p][sum];
		T res{};
		int up = limit ? s[p] - '0' : 9;
		for (int i = 0; i <= up; ++i) {
			res = (res + dfs(p + 1, sum + i,  limit && i == up)) % M;
		}
		if (!limit)
			f[p][sum] = res;
		return res;
	};
	return dfs(0, 0, true);
}

class Solution {
public:
    int count(string s1, string s2, int min_sum, int max_sum) {
    	auto chk = [&](string &s) {
    		int sum = 0;
    		for (auto &c : s) 
    			sum += c - '0';
    		return sum >= min_sum && sum <= max_sum;
    	};
        return (dp(s2, min_sum, max_sum) - dp(s1, min_sum, max_sum) + M + chk(s1)) % M;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string s1, s2;
    int mn, mx;
    cin >> s1 >> s2 >> mn >> mx;
    Solution so;
    cout << so.count(s1, s2, mn, mx) << '\n';

    return 0;
}
