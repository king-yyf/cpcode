#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://projecteuler.net/problem=6

using i128 = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    i128 n = 100;

    i128 s = n * (n + 1) / 2;

    i128 s1 = n * (n + 1) / 2 * (2 * n + 1) / 3;

    i128 ans = s * s - s1;
   
    cout << ans << '\n';
    return 0;
}
