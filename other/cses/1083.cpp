#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n - 1; ++i) {
        int x;
        cin >> x;	
        x --;
        a[x] = 1;
    }
    for (int i = 0; i < n; ++i) {
        if (!a[i]) cout << i + 1 << "\n";	
    }

    return 0;
}
