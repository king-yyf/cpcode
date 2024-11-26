#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, t, c;
    cin >> n;
    vector<int> in(n);
    for (int i = 0, x; i < n; ++i) {
    	cin >> x;
    	x -= 1;
    	if (i != x) {
    		in[x]++;
    	}
    }

    vector<array<int, 2>> ans;

    for (auto &a : p) {
    	c = 0;
    	for (auto &x : a) {
    		if (in[x] == 0) {
    			c++;
    		} else {
    			t = x;
    		}
    	}
    	if (c == 0) continue;
    	for (auto &x : a) {
    		if (in[x] == 0) {
    			ans.push_back({t, x});
    		}
    	}
    }

    cout << ans.size() << "\n";

    for (auto &[x, y] : ans) {
    	cout << x + 1 << " " << y + 1 << "\n";
    }
    
    return 0;
}
