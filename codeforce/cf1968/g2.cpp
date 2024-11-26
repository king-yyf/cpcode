#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> z_function(string& s) {
    int n = s.size();
    vector<int> z(n, n);
    for (int i = 1, l = 0, r = 0; i < n; i += 1) {
        if (i <= r and z[i - l] < r - i + 1) z[i] = z[i - l];
        else for (z[i] = max(0, r - i + 1); i + z[i] < n && s[z[i]] == s[i + z[i]]; z[i] += 1);
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    string s;
    cin >> s;
    auto z = z_function(s);

    set<int> id{n};
    set<pair<int,int>> S;
    for (int i = 1; i < n; ++i) {
        id.insert(i);
        S.insert({z[i], i});
    }

    vector<int> cnt(n + 1, 1);
    // cnt[i]: 长度为i的前缀最多能划分cnt[i]段
    cnt[0] = n;
    for (int k = 1; k < n; ++k) {
        while (!S.empty() && S.begin()->first < k) {
            id.erase(S.begin()->second);
            S.erase(S.begin());
        }
        for (int i = k; i < n;) {
            i = *id.lower_bound(i);
            if (i == n) break;
            i += k, cnt[k]++;
        }
    }

    vector<int> ans(n + 1, 0);

    for (int i = 1, j = n; i <= n; ++i) {
        while (j > 0 && cnt[j] < i) {
            j--;
        }
        ans[i] = j;
    }

    for (int i = l, j = 0; i <= r; ++i) {
        cout << ans[i] << " \n"[i == r];
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
