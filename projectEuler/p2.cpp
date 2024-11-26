#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://projecteuler.net/problem=2

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int x = 1, y = 2, z = x + y;
    long long s = 2;

    while (z <= 4000000) {
    	if (z % 2 ==0) s += z;
    	x = y, y = z;
    	z = x + y;
    }

    cout << s << '\n';

    return 0;
}
