#include<bits/stdc++.h>
using namespace std;


/*

given the skill values of n developers, find k teams with lowest inefficlencies among all possible pairs of teams, return their inefficiencies sorted ascending.
*/

long long count_good_paths(vector<vector<long long>> &a, long long k) {
    int n = a.size(), m = a[0].size();
    long long res = 0;

    map<long long, long long> mp[n];

    function<void(int, int, long long)> dfs_pre = [&](int x, int y, long long s) {
        if (x + y == (n + m - 2) / 2) {
            mp[x][s]++;
            return;
        }
        if (x + 1 < n) dfs_pre(x + 1, y, (s + a[x + 1][y]) % k);
        if (y + 1 < m) dfs_pre(x, y + 1, (s + a[x][y + 1]) % k);
    };
 
    function<void(int, int, long long)> dfs_suf = [&](int x, int y, long long s) {
        if (x + y == (n + m - 2) / 2) {
            if (mp[x].count(k - ((s - a[x][y] + k) % k))) 
                res += mp[x][k - ((s - a[x][y] + k) % k)];
            return;
        }
        if (x > 0) dfs_suf(x - 1, y, (s + a[x - 1][y]) % k);
        if (y > 0) dfs_suf(x, y - 1, (s + a[x][y - 1]) % k);
    };

    dfs_pre(0, 0, a[0][0] % k);
    dfs_suf(n - 1, m - 1, a[n - 1][m - 1] % k);

    return res;
}

int main() {
	int n, m;
	long long k, res = 0;
	cin >> n >> m >> k;
	vector a(n,vector<long long> (m));
	for (int i = 0 ; i < n; ++i) 
		for (int j = 0; j < m; ++j) 
			cin >> a[i][j];

	// map<long long, long long> mp[n];

	// function<void(int, int, long long)> dfs_pre = [&](int x, int y, long long s) {
	// 	if (x + y == (n + m - 2) / 2) {
	// 		mp[x][s]++;
	// 		return;
	// 	}
	// 	if (x + 1 < n) dfs_pre(x + 1, y, s ^ a[x + 1][y]);
	// 	if (y + 1 < m) dfs_pre(x, y + 1, s ^ a[x][y + 1]);
	// };

	// function<void(int, int, long long)> dfs_suf = [&](int x, int y, long long s) {
	// 	if (x + y == (n + m - 2) / 2) {
	// 		if (mp[x].count(s ^ k ^ a[x][y])) 
	// 			res += mp[x][s ^ k ^ a[x][y]];
	// 		return;
	// 	}
	// 	if (x > 0) dfs_suf(x - 1, y, s ^ a[x - 1][y]);
	// 	if (y > 0) dfs_suf(x, y - 1, s ^ a[x][y - 1]);
	// };

	// dfs_pre(0, 0, a[0][0]);
	// dfs_suf(n - 1, m - 1, a[n - 1][m - 1]);

	cout << count_good_paths(a, k) << "\n";
}