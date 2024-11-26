#include<bits/stdc++.h>
using namespace std;

int minimumOperations(int n, vector<int> &a) {
	int mx = *max_element(a.begin(), a.end());
	for (auto &x : a)
		x = (x == mx);
	int ans = 0, len = 0, cur = a[n - 1];
	bool last = 0;
	while (a.size()) {
		int cnt = 0;
		while (a.size() && a.back() == cur) {
			cnt ++;
			a.pop_back();
		}
		if (cur == 0) {
			ans += (cnt + 1) / 2;
			if (last && cnt % 2 && len == 1) {
				ans--;
				last = 0;
				len = 0;
			} else last = cnt % 2;
		} else len = cnt;
		cur ^= 1;
	}
	return ans;
}

int minimumOperations(int n, vector<int> &a) {
	int mx = *max_element(a.begin(), a.end());
	for (auto &x : a)
		x = (x == mx);
	int ans = 0, cnt = 0, last = 0, len = 0;
	for (int i = 0; i < n; ++i) {
		if (i == 0 || a[i] == a[i - 1]) {
			cnt++;
		} else {
			if (a[i - 1] == 0) {
				ans += (cnt + 1) / 2;
				if (last && cnt % 2 && len == 1) {
					ans--, last = 0, len = 0;
				} else last = cnt % 2;
			} else {
				len = cnt;
			}
			cnt = 1;
		}
	}
	return ans; 
}

int main() {

}