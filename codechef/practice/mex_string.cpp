#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
s为二进制字符串
Mex(s):最小的非负整数，使得该数的二进制表示不是s的子序列，求mex(s)的值。

输出其二进制表示
1<=s.size()<=1e6
link: https://www.codechef.com/problems/MEXSTR
rating: 2048
*/

void solve() {
	string s;
	cin >> s;
	int n = s.size();
	vector<array<int, 2>> dp(n + 1);
	for (int i = n - 1; i >= 0; --i) {
		dp[i] = dp[i + 1];
		dp[i][s[i] - '0'] = min(dp[i + 1][0], dp[i + 1][1]) + 1;
	}

	if (dp[0][0] == 0) {
		cout << '0' << '\n';
		return;
	}

    string ans = "1";
    for (int i = 0, cur = dp[0][1] + 1, num = 1; i < n - 1; ++i) {
    	if (num == s[i] - '0') {
    		cur--;
    		num = cur <= dp[i + 1][0];
    		ans += cur <= dp[i + 1][0] ? '1' : '0';
    	}
    }
    
    while (ans.size() < dp[0][1] + 1) {
    	ans += '0';
    }
    
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
    	solve();
    }

    return 0;
}
