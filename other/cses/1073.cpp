#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1073

void wt(vector<int> &a){
    for(int x:a)cout<<x<<' ';cout<<'\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> res;
    for (int i = 0; i < n; ++i) {
        auto it = upper_bound(res.begin(), res.end(), a[i]);
        if (it == res.end()) res.push_back(a[i]);
        else *it = a[i];
    }

    cout << res.size() << '\n';

    return 0;
}
