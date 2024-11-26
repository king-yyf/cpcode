#include<bits/stdc++.h>
using namespace std;

int minScore(vector<int> &a, int k) {
	int n = a.size();

	int l = 0, r = 1e9;

	int ans = r;

	auto chk = [&](int x) {
		long long s = 0;
		int mx = 0, used = 0;
		for (int i = 0; i < n; ++i) {
			s += a[i];
			mx = max(mx, a[i]);
			if (s >= x && !used) {
				s -= min(mx, k);
				used = 1;
			}
		}
		return s < x;
	};

	while (l <= r) {
		int mid = (l + r) / 2;
		if (chk(mid)) {
			ans = mid;
			r = mid - 1;
		} else l = mid + 1;
	}

	return ans;
}

int main(){
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int &x :a) {
		cin >> x;
	}
	int p = minScore(a, k);
	cout << p << "\n";
}