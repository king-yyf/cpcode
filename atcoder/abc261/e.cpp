#include<bits/stdc++.h>
using namespace std;
#define bit(x,i) (((x)>>(i))&1)

int main() {
    int n, x, s0 = 0, s1 = (1 << 30) - 1, m = s1;
    cin >> n >> x;
    for (int i = 0, t, a; i < n; ++i) {
        cin >> t >> a;
        if (t == 1) s1 &= a, s0 &= a;
        else if (t == 2) s1 |= a, s0 |= a;
        else s1 ^= a, s0 ^= a;
        x = (x & s1) | ((x ^ m) & s0);
        cout << x << "\n";
    }
}