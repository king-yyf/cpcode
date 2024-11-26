#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// https://vjudge.net/problem/CSES-2185

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    long long n, k;
    cin >> n >> k;
    vector<long long> a(k);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];	
    }
    long long ans = 0;
    function<void(int, long long, bool)> dfs = [&](int p, long long s, bool odd) {
    	if (p >= k) {
    		if (s == 1) return;
    		if (!odd) ans -= n / s;
    		else ans += n / s;
    		return;
    	}
    	dfs(p + 1, s, odd);

    	if (a[p] <= n / s) dfs(p + 1, s * a[p], odd ^ 1);
    };
    dfs(0, 1, 0);
    cout << ans << '\n';
    return 0;
}
