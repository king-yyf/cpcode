#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;
vector<int> divs[MX];

void solve() {
    int n, m;
    cin >> n;
    vector<int> a(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        m = max(a[i], m);
    }
    vector<vector<int>> p(m + 1);
    vector<int> ind(m + 1);

    for (int i = 0; i < n; ++i) 
        p[a[i]].push_back(i);

    vector<int> lmx(n, -1), rmx(n, n), lmn(n, -1), rmn(n, n);

    vector<int> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && a[sk.back()] < a[i]) {
            rmx[sk.back()] = i;
            sk.pop_back();
        }
        sk.push_back(i);
    }
    sk.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && a[sk.back()] <= a[i]) {
            lmx[sk.back()] = i;
            sk.pop_back();
        }
        sk.push_back(i);
    }
    sk.clear();
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && a[sk.back()] > a[i]) {
            rmn[sk.back()] = i;
            sk.pop_back();
        }
        sk.push_back(i);
    }
    sk.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && a[sk.back()] > a[i]) {
            lmn[sk.back()] = i;
            sk.pop_back();
        }
        sk.push_back(i);
    }

    auto get = [&](int x1, int y1, int x2, int y2) {
        return max(0, min(y1, y2) - max(x1, x2));
    };

    long long ans = 0;

    for (int i = 0; i < n; ++i) {
        for (int x : divs[a[i]]) {
            if (ind[x] >= 1) {
                int j = p[x][ind[x] - 1];
                ans += get(lmx[i], i, lmn[j], j) * 1ll * get(i, rmx[i], j, rmn[j]);
            }
            if (ind[x] < p[x].size()) {
                int j = p[x][ind[x]];
                int t = ind[x] >= 1 ? p[x][ind[x] - 1] : -1;
                ans += get(max(t, lmx[i]), i, lmn[j], j) * 1ll * get(i, rmx[i], j, rmn[j]);
            }
        }
        ind[a[i]]++;
    }
    cout << ans << "\n";

}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    for (int i = 1; i < MX; ++i) {
        for (int j = i; j < MX; j += i) {
            divs[j].push_back(i);
        }
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}