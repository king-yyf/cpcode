#include <bits/stdc++.h>
using namespace std;

int minimumLengStr(string &s, int k) {
	int n = s.size();
	vector<long long> a(n, 1);
	long long sum = 1;
	for (int i = 0; sum < k; i = (i + 1) % n) {
		sum = sum / a[i] * (a[i] + 1);
		++a[i];
	}

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += a[i];		
	}

	return ans;
}

int main() {
	string s;
	int k;
	cin >> s >> k;
	cout << minimumLengStr(s, k) << "\n";
    return 0;
}
