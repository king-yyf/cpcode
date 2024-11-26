#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    sort(a.begin(), a.end());

    long long s = 0;
    for (int i = 0; i < n; ++i) {
        s += abs(a[i] - a[n / 2]);	
    }
    cout << s << '\n';

    return 0;
}
