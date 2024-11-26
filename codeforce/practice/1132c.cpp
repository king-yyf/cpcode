#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;

    vector<array<int, 2>> qs(q);

    vector<int> d(n + 1);

    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        qs[i] = {x, y};
    	d[x]++;
        if (y + 1 <= n) d[y + 1]--;
    }
    for (int i = 1; i <= n; ++i)
        d[i] += d[i - 1];

    vector<int> s1(n + 1), s2(n + 1);

    int tot = 0, ans = n + 1;
    for (int i = 1; i <= n; ++i) {
        if (d[i] > 0) tot++;
        s1[i] = s1[i - 1] + (d[i] == 1);
        s2[i] = s2[i - 1] + (d[i] == 2);
    }

    sort(qs.begin(), qs.end());

    for (int i = 0; i < q; ++i) {
    	int x = qs[i][0], y = qs[i][1];
    	for (int j = i + 1; j < q; ++j) {
    		int l = qs[j][0], r = qs[j][1];
            int cur = 0, r1 = min(r, y), r2 = max(r, y);
            if (r1 - l + 1 > 0) {
                cur += s2[r1] - s2[l - 1];
                if (x <= l - 1) cur += s1[l - 1] - s1[x - 1];
                if (r1 + 1 <= r2) cur += s1[r2] - s1[r1];
            } else {
                cur += s1[y] - s1[x - 1];
                cur += s1[r] - s1[l - 1];
            }
            ans = min(ans, cur);
    	}
    }

    cout << tot - ans << "\n";

    return 0;
}
