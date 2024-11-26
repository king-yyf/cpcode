#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    multiset<int> l, r;
    vector<array<int, 2>> a(n);
    for (int i = 0, u, v; i < n; ++i) {
    	cin >> u >> v;
    	l.insert(u);
    	r.insert(v);
    	a[i] = {u, v};
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
    	l.erase(l.find(a[i][0]));
    	r.erase(r.find(a[i][1]));
    	int cur = *r.begin() - *l.rbegin();
    	ans = max(ans, cur);
    	l.insert(a[i][0]);
    	r.insert(a[i][1]);
    }
    cout << ans << '\n';

    return 0;
}
