#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    long long s = -1e18, p = 0;
    for (int i = 0; i < n; ++i) {
    	p += a[i];
    	s = max(s, p);
    	if (p < 0) p = 0;
    }
    cout << s << '\n';
    return 0;
}
