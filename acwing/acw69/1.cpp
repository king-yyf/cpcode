#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x, y, a, b;
    cin >> x >> y >> a >> b;

    if((y - x) % (a + b) == 0)
    	cout << (y - x) / (a + b) << "\n";
    else cout << "-1\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    while (T--) {
    	solve();
    }

    return 0;
}
