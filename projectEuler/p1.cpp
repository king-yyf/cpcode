#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int s = 0;
    for (int i = 1; i < 1000; ++i)
    	if (i % 3 == 0 || i % 5 == 0)
    		s += i;
    cout << s << '\n';

    return 0;
}
