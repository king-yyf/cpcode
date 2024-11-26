#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    set<int> s;
    for (int i = 0; i < n; ++i) {
        s.insert(i);
    }
    vector<pair<int,int> > ans;
    for (int i = n - 1; i > 0; --i) {
        vector<int> occ(i, -1);
        for (int j : s) {
            if (occ[a[j] % i] != -1) {
                ans.emplace_back(j, occ[a[j] % i]);
                s.erase(j);
                break;
            }
            occ[a[j] % i] = j;
        }
    }
    cout << "YES\n";
    for (int i = ans.size() - 1; i >= 0; --i) {
        cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
