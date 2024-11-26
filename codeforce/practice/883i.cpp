#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a){
    for(int x:a)
        cout<<x<<' ';
    cout<<'\n';
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    sort(a.begin(), a.end());

    int l = 0, r = 1e9 + 2, ans = r;

    auto chk = [&](int x) {
        vector<int> f(n + 1);
        f[0] = 1;
        for (int i = 1, j = 1, s = 0; i <= n; ++i) {
            if (i >= k) s += f[i - k];
            while (a[i - 1] - a[j - 1] > x) {
                s -= f[j - 1];
                j++;
            }
            f[i] = s > 0;
        }
        return f[n];
    };

    while (l <= r) {
        int md = (l + r) / 2;
        if (chk(md)) {
            ans = md;
            r = md - 1;
        } else {
            l = md + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
