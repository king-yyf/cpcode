#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> p2(n + 1), p5(n + 1);

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        p2[i] = p2[i - 1];
        p5[i] = p5[i - 1];

        while (x % 2 == 0) {
            p2[i]++;
            x /= 2;
        }
        while (x % 5 == 0) {
            p5[i]++;
            x /= 5;
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            ans += min(p2[j + 1] - p2[i], p5[j + 1] - p5[i]);
        }
    }

    cout << ans << "\n";

    return 0;
}
