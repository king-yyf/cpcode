#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    long long s = 1;
    for (int i = 1; i <= 20; i += 1) {
    	s = lcm(s, i);
    }

    cout << s << '\n';

    return 0;
}
