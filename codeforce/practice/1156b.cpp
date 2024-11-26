#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
	string s;
	cin >> s;
	string odd = "", even = "";
	int n = s.size();
	for (int i = 0; i < n; ++i) {
		if (s[i] & 1) odd += s[i];
		else even += s[i];
	}
	sort(odd.begin(), odd.end());
	sort(even.begin(), even.end());
	auto chk = [&](string &t) {
		for (int i = 0; i < n - 1; ++i) {
			if (abs(t[i] - t[i + 1]) == 1) 
				return 0;
		}
		return 1;
	};
	string t = odd + even;
	if (chk(t)) {
		cout << t << "\n";
		return;
	}
	t = even + odd;
	if (chk(t)) {
		cout << t << "\n";
		return;
	}

	cout << "No answer\n";

}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
    	solve();
    }

    return 0;
}
