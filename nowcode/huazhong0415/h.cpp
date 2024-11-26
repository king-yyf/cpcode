#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    set<vector<int>> s;
    for (int i = 0; i < n; ++i) {
        if (a[i] > b[i]) swap(a[i], b[i]);
        s.insert({b[i], i ,1});
    }
    int ans = INT_MAX;
    while (s.size() == n) {
        ans = min(ans, (*s.rbegin())[0] - (*s.begin())[0] );
        auto p = *s.rbegin();
        s.erase(prev(s.end()));
        if (p[2] == 1) {
            s.insert({a[p[1]], p[1], 0});
        } else break;
    }
    cout << ans;
    return 0;
}
