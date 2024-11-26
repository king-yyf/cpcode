#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<array<int, 2>> ops(n + 1, {1, 0});
	for (int i = 1; i <= n; ++i) {
		cin >> ops[i][0] >> ops[i][1];
	}
	long long ans = -1e18, s = 0;
	priority_queue<int> q;

	for (int i = n; i >= 0 && k >= 0; --i) {
		if (ops[i][0] == 1) {
			ans = max(ans, s + ops[i][1]);
			k--;
		} else {
			if (ops[i][1] < 0) {
				q.push(ops[i][1]);
			} else s += ops[i][1];
		}
		while (q.size() > k) {
			s += q.top();
			q.pop();
		}
	}
	cout << ans << "\n";
}