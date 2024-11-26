#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-2217

void wt(vector<int> &a){
    for(int x:a)cout<<x<<' ';cout<<'\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n), p(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
        p[a[i]] = i;
    }

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        ans += i == 0 || (p[i] < p[i - 1]);
    }

    for (int i = 0, x, y, u, v; i < m; ++i) {
        cin >> u >> v;
        u--, v--;

        x = a[u], y = a[v];

        if (x == 0 || p[x] < p[x - 1]) ans--;
        if (x < n - 1 && p[x] > p[x + 1]) ans--;
        p[x] = v;
        if (x == 0 || p[x] < p[x - 1]) ans++;
        if (x < n - 1 && p[x] > p[x + 1]) ans++;

        if (y == 0 || p[y] < p[y - 1]) ans--;
        if (y < n - 1 && p[y] > p[y + 1]) ans--;
        p[y] = u;
        if (y == 0 || p[y] < p[y - 1]) ans++;
        if (y < n - 1 && p[y] > p[y + 1]) ans++;
        swap(a[u], a[v]);
        
        cout << ans << '\n';

    }

    return 0;
}
