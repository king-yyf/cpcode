#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false); 
    cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	vector<int> c(n + 1);
	for (int i = 0; i < q; ++i) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		c[x]++, c[y + 1]--;
	}
	for (int i = 0; i < n; ++i) 
		c[i + 1] += c[i];
	c.pop_back();
	sort(a.begin(), a.end());
	sort(c.begin(), c.end());
	long long s = 0;
	for (int i = 0; i < n; ++i) {
		s += a[i] * 1ll * c[i];
	}
	cout << s << "\n";
}
