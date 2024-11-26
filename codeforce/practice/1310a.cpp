#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n), t(n), p(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    for (int i = 0; i < n; ++i) {
        cin >> t[i];	
    }

    iota(p.begin(), p.end(),0);
    sort(p.begin(), p.end(), [&](int i, int j){
    	return a[i] < a[j];
    });

    long long ans = 0;
    set<pair<int, int>> s;
    for (int i = 0, j = 0, x = 0; i < n; ++i, ++x) {
    	if (i == j) x = a[p[i]];
    	while (j < n && a[p[j]] == x) {
            s.emplace(-t[p[j]], p[j]);
            ++j;
        }
        int k = s.begin() -> second;
        s.erase(s.begin());
        ans += 1ll * (x - a[k]) * t[k];
    }

    cout << ans << '\n';

    return 0;
}
