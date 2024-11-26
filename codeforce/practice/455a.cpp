#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, x;
    cin >> n;
    map<int, ll> mp;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        mp[x] += x;	
    }
 
    vector<pair<int,ll> > a;
    for (auto &[k, v]: mp) {
    	a.emplace_back(k, v);
    }

    n = a.size();

    vector<long long> f(n + 1), g(n + 1);

    f[1] = a[0].second;

    for (int i = 1; i < n; ++i) {
    	if (a[i].first == a[i - 1].first + 1) {
    		f[i + 1] = max(f[i], g[i] + a[i].second);
    		g[i + 1] = max(f[i], g[i]);
    	}else {
    		f[i + 1] = max(f[i], g[i]) + a[i].second;
    		g[i + 1] = max(f[i], g[i]);
    	}
    }

    cout << max(f[n], g[n]) << '\n';

    return 0;
}
