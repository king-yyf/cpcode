#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false); 
    cin.tie(nullptr);
	long long n, m, k;
	cin >> n >> m >> k;
	if (n > m) swap(n, m);
	long long  l = 1, r  = n * m, ans = -1;
	while (l <= r) {
		long long  md = (l + r) / 2;
		long long t = 0;
		for (long long i = 1; i <= n; ++i) {
			if (i * m < md) t += m;
			else t += md / i;
			if (t >= k) break; 
		}
		if (t >= k) {
			ans = md;
			r = md - 1;
		}else {
			l = md + 1;
		}
	}
	cout << ans << "\n";
}
