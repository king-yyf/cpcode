#include <bits/stdc++.h>
using namespace std;
// https://codeforces.com/contest/1064/problem/B

void solve() {
    int a;
    cin >> a;
    int ans = 1 << __builtin_popcount(a);
    cout <<  ans << "\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    while(T--) {
    	solve();
    }

    return 0;
}
