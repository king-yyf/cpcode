#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
	string s;
	cin >> s;
	int n = s.size();
	long long ans = 0;
	int oo = 0, oe = 0, eo = 0, ee = 0;
	vector<int> pre(n + 1, -1);
	for (int i = 1; i <= n; i++) {
	    if (s[i - 1] == '0') {
	        if (i & 1) {
	            oe = i;
	            pre[i] = max(oo, ee);
	        }
	        else {
	            ee = i;
	            pre[i] = max(eo, oe);
	        }
	    }
	    else if (s[i - 1] == '1') {
	        if (i & 1) {
	            oo = i;
	            pre[i] = max(oe, eo);
	        }
	        else {
	            eo = i;
	            pre[i] = max(ee, oo);
	        }
	    }
	}
	for (int i = 1, now = 0; i <= s.length(); i++) {
	    now = max(now, pre[i]);
	    ans += i - now;
	}
	cout << ans << '\n';
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
