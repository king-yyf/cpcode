#include<bits/stdc++.h>
using namespace std;

int maxSocre(vector<int> &a) {
    int n = a.size();
    vector g(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            g[i][j] = gcd(a[i], a[j]);

    vector dp(n + 1,vector<int> (1 << n));

    function<int(int, int)> dfs =[&](int idx, int st) {
        if (idx - 1 == n / 2) return 0;
        if (dp[idx][st]) return dp[idx][st];
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if ((st >> i) & 1) continue;
            for (int j = i + 1; j < n; ++j) {
                if ((st >> j) & 1) continue;
                res = max(res, idx * g[i][j] + dfs(idx + 1, st | (1 << i) | (1 << j)));
            }
        }
        return dp[idx][st] = res;

    };
    
    return dfs(1, 0);
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for(auto&x:a)
		cin >> x;
	cout<<maxSocre(a)<<"\n";
}