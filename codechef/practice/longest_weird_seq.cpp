#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
link: https://www.codechef.com/problems/LWS
solution:https://discuss.codechef.com/t/lws-editorial/893
*/

int lws(string &s) {
	int n = s.size(); 
	vector f(26, vector<int>(26));
	for (int i = 0; i < n; ++i) {
		int t = s[i] - 'a';
		auto g = f;
		for (int x = 0; x < 26; ++x) {
			for (int y = 0; y < 26; ++y) {
				if (x <= t) g[t][y] = max(g[t][y], f[x][y] + 1);
				if (y >= t) g[x][t] = max(g[x][t], f[x][y] + 1);
			}
		}
		g.swap(f);
	}
	int ans = 0;
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < 26; ++j) 
			ans = max(ans, f[i][j]);
	}
	return ans;
}

void solve() {
	string s;
	cin >> s;
	cout << lws(s) << '\n';
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
