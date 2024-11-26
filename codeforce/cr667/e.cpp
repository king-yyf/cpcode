#include<bits/stdc++.h>
using namespace std;

void slove() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n), b(n);
	for (auto &x : a) 
		cin >> x;
	for (auto &x : b) 
		cin >> x;

	sort(a.begin(), a.end());

	vector<int> pref(n), surf(n);

	for (int i = 0, j = 0; i < n; i++) {
		while (j + 1 < n && a[j + 1] - a[i] <= k) {
			j++;
		}
		surf[i] = j - i + 1;
	}
	for (int i = n - 1, j = n - 1; i >= 0; --i) {
		while (j - 1 >= 0 && a[i] - a[j - 1] <= k) {
			j--;
		}
		pref[i] = i - j + 1;
	}

	for (int i = 1; i < n; ++i) {
		pref[i] = max(pref[i], pref[i - 1]);
		surf[n - i - 1] = max(surf[n - i - 1], surf[n - i]);
	}

	int ans = 1;
	for (int i = 0; i < n - 1; ++i) {
		int x = i < n - 1 ? surf[i + 1] : 0;
		ans = max(ans, x + pref[i]);
	}
	cout << ans << "\n";
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		slove();
	}
}