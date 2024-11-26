#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1163

void wt(vector<int> &a){
    for(int x:a)cout<<x<<' ';cout<<'\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int x, n;
    cin >> x >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    multiset<int> s{0, x};
    for (int i = 0; i < n; ++i) {
        s.insert(a[i]);
    }

    int t = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) 
            t = max(t, *it - *prev(it));
    }

    vector<int> res(n);

    for (int i = n - 1; i >= 0; --i) {
        int x = a[i];
        s.erase(s.find(x));
        res[i] = t;
        auto it = s.lower_bound(x);

        t = max(t, *it - *prev(it));
        t = max(t, *next(it) - (*it));
    }

    for (int i = 0; i < n; ++i) {
        cout << res[i] << " \n"[i == n - 1];
    }

    return 0;
}
