#include <bits/stdc++.h>
using namespace std;

vector<long long> countPermulationMEX(vector<int> &a) {
    int l, r, n = a.size();
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[a[i]] = i;
        if (a[i] == 0) l = i, r = i;
    }
    
    vector<long long> ans(n);
    ans[n - 1] = 1;
    for (int i = 0; i < n - 1; ++i) {
        int k = p[i + 1];
        if (l > k) {
            ans[i] = (n - r) * 1ll * (l - k);
            l = k;
        } else if (r < k) {
            ans[i] = (l + 1ll) * (k - r);
            r = k;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);cin.tie(nullptr);

    int T = 1, n;
    cin >> T;
    while (T--) {
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        auto ans = countPermulationMEX(a);
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << " \n"[i == n - 1];    
        }
    }
    return 0;
}
