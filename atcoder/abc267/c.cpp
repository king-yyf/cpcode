#include <bits/stdc++.h>
using namespace std;

long long maxKIndexSum(vector<int> &a, int m) {
    int n = a.size();
    vector<long long> p(n + 1), s(n - m + 1);
    for (int i = 0; i < n; ++i) p[i + 1] = p[i] + a[i];
    for (int i = 0; i < n; ++i) {
        if (i < m) s[0] += (i + 1ll) * a[i];
        else {
            s[i - m + 1] = s[i - m] + m * a[i] - (p[i] - p[i - m]);
        }
    }
    return *max_element(s.begin(), s.end());
}

/*


1 * a[i-1] + 2 * a[i+1] + ... + m *a[i+m-2]

1 * a[i] + ... +        (m-1) *a[i+m-2] + m * a[i+m-1]

= m*a[i+m-1] + s - (a[i-1]+a[i+1]+...+a[i+m-2])


5 4 -1 8

1 : 5 * 1 + 4 * 2
2 : 4 * 1 + (-1) * 2
3: (-1) * 1 + 8 * 2
*/

long long solve(vector<int> &a, int m) {
    int n = a.size();
    long long s = 0, ans = -1e18;
    vector<long long> p(n + 1);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + a[i];
    }
    for (int i = 0; i < m; ++i) {
        s += (i + 1ll) * a[i]; 
    }
    ans = s;

    for (int i = 1; i + m <= n; ++i) {
        long long t = s + m * 1ll * a[i + m - 1] - (p[i + m - 1] - p[i - 1]);
        ans = max(ans, t);
        s = t;
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto&x: a) 
        cin >> x;
    cout << solve(a, m) << "\n";
}