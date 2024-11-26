#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string s;
    cin >> s;
    int n = s.size();
    long long ans = 0, a = 0, b = 0;

    for (int l = 0, r = 0; l < n; ++l) {
    	while (r < n && a < 3 && b < 3) {
    		s[r] == '1' ? (a++) : (b++);
    		r++;
    	}
    	if (max(a, b) >= 3) {
    		ans += n - r + 1;
    	}
    	s[r] == '1' ? (a--) : (b--);
    }

    cout << ans << "\n";

    return 0;
}