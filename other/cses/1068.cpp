#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    long long  n;
    cin >> n;
    while (1) {
    	if (n == 1) break;
    	cout << n << ' ';
    	if (n % 2 == 0) n /= 2;
    	else n  = n * 3 + 1;
    }
    cout << n << "\n";

    return 0;
}
