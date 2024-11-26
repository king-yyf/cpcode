#include<bits/stdc++.h>
using namespace std;

int maxModPair(vector<int> &a){
	int n = a.size(), ans = 0;
	sort(a.begin(), a.end());
	for (int i = 0; i < n; ++i) {
		if (i > 0 && a[i] == a[i - 1]) continue;
		for (int j = 2 * a[i]; j <= a[n - 1] + a[i]; j += a[i]) {
			if (ans + 1 >= a[i]) break;
			int pos = lower_bound(a.begin(), a.end(), j) - a.begin() - 1;
			if (pos >= 0) {
				ans = max(ans, a[pos] % a[i]);
			}
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false); 
    cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	cout << maxModPair(a);
}
