#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1662

void mod(int &x, int n) {
	x %= n;
	if (x < 0) x += n;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n + 1), p(n);
    for (int i = 1; i <= n; ++i) {
    	cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
    	a[i + 1] += a[i];
    	mod(a[i + 1], n);
    }

    long long ans = 0;
    for (int i = 0; i <= n; ++i) {
    	ans += p[a[i]];
    	p[a[i]]++;
    }
    cout << ans << '\n';

    return 0;
}
