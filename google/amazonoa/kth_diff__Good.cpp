#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    sort(a.begin(), a.end());

    vector<int> p;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            p.push_back(a[j] - a[i]);
        }
    }

    sort(p.begin(), p.end());

    cout << p[k - 1] << '\n';

    return 0;
}
