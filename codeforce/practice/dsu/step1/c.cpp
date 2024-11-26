#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 10;

ll f[N], w[N], val[N];

int get(int x) {
    return x == f[x] ? x : f[x] = get(f[x]);
}

void merge(int x, int y) {
    x = get(x), y = get(y);
    if (x == y) return;
    f[x] = y;
    w[x] -= w[y];
}

ll calc(int x) {
    if (f[x] == x) return val[x] + w[x];
    return val[x] + w[x] + calc(f[x]);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    string s;

    for (int i = 0; i < n; ++i) {
        f[i] = i;
    }

    for (int i = 0, x, y; i < m; ++i) {
        cin >> s;
        if (s[0] == 'j') {
            cin >> x >> y;
            merge(--x, --y);
        } else if (s[0] == 'a'){ 
            cin >> x >> y;
            x--;
            w[get(x)] += y;
        } else {
            cin >> x;
            x--;
            cout << calc(x) << '\n';
        }

    }

    return 0;
}
