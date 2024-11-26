#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    
    vector<int> f(n),g(n);
	f[0] = 1, g[n - 1] = 1;
	int ans = 1;
	for (int i = 1; i < n; ++i) {
		f[i] = a[i] > a[i - 1] ? f[i - 1] + 1 : 1;
		ans = max(ans, f[i]);
	}
	for (int i = n - 2; i >= 0; --i) {
		g[i] = a[i] < a[i + 1] ? g[i + 1] + 1 : 1;
		ans = max(ans, g[i]);
	}
	for (int i = 1; i < n - 1; ++i) {
		if (a[i - 1] < a[i + 1]) ans = max(ans, f[i - 1] + g[i + 1]);
	}
	cout << ans << '\n';
    return 0;
}
