#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int  n;
    cin >> n;

    for (long long i = 1; i <= n; ++i) {
    	cout << (i - 1) * (i + 4) * (i * i - 3 * i + 4)/2 << "\n";
    }

    return 0;
}

/*
0,6,28,96,252,550,1056,1848

*/