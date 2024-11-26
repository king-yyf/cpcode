#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://projecteuler.net/problem=4

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int ans = -1;

    for (int x = 100; x <= 999; ++x)
    	for (int y = 100; y <= 999; ++y) {
    		int t = x * y;
    		string s = to_string(t);
    		auto s2 = s;
    		reverse(s2.begin(), s2.end());
    		if (s2 == s && t > ans) ans = t;
    	}

    cout << ans << '\n';

    return 0;
}
