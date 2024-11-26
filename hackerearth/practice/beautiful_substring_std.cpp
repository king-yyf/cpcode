#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int M = 1000000007;
const int N = 2000005;

int t[N][2], a[N], dp[N], fa[N];
int nxt = 1;
vector<int> v[N];

int ans = 0;

void add(string &s) {
	int node = 0;
	for (int i = 0; i < s.size(); ++i) {
		int x = s[i] - 'a';
		if (t[node][x] == 0) {
			v[node].push_back(nxt);
			a[nxt] = x;
			fa[nxt] = node;
			node = t[node][x] = nxt;
			nxt += 1;
		} else {
			node = t[node][x];
		}
	}
}

void dfs(int u, int p, int c) {
	if (a[u] == 1) {
		if (p > 0) {
			dp[u] = 1;
			if (fa[p] != -1 and a[fa[p]] == 1) {
				dp[u] = (dp[u] + dp[fa[p]]) % M;
			}
		}
		p = u;
	}
	c = (c + dp[u]) % M;
	ans = (ans + c) % M;
	for (auto i : v[u]) 
		dfs(i, p, c);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
    	string s;
    	cin >> s;
    	add(s);
    }

    fa[0] = -1;

    dfs(0, -1, 0);

    cout << ans << '\n';

    return 0;
}
